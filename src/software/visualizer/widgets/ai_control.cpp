#include "software/visualizer/widgets/ai_control.h"

#include <QtWidgets/QComboBox>
#include <QtWidgets/QPushButton>

#include "software/ai/hl/stp/play/play.h"
#include "software/logger/logger.h"
#include "software/parameter/dynamic_parameters.h"
#include "software/util/design_patterns/generic_factory.h"

void setupAIControls(Ui::AutoGeneratedMainWidget *widget,
                     std::shared_ptr<ThunderbotsConfig> config)
{
    setupAIStartAndStopButtons(widget, config);
    setupTeamColourComboBox(widget, config);
    setupDefendingSideComboBox(widget, config);
    setupGameStateOverrideComboBox(widget, config);
    setupPlayOverrideComboBox(widget, config);
}

void setupAIStartAndStopButtons(Ui::AutoGeneratedMainWidget *widget,
                                std::shared_ptr<ThunderbotsConfig> config)
{
    auto start_ai_func = [config]() {
        config->getMutableAIControlConfig()->mutableRunAI()->setValue(true);
    };
    QWidget::connect(widget->start_ai_button, &QPushButton::clicked, start_ai_func);
    auto stop_ai_func = [config]() {
        config->getMutableAIControlConfig()->mutableRunAI()->setValue(false);
    };
    QWidget::connect(widget->stop_ai_button, &QPushButton::clicked, stop_ai_func);
}

void setupTeamColourComboBox(Ui::AutoGeneratedMainWidget *widget,
                             std::shared_ptr<ThunderbotsConfig> config)
{
    widget->team_colour_combo_box->insertItem(0, "Yellow");
    widget->team_colour_combo_box->insertItem(1, "Blue");
    widget->team_colour_combo_box->insertItem(2, "Use Refbox");
    auto on_team_colour_changed = [config](const QString &text) {
        auto refbox_config =
            config->getMutableAIControlConfig()->getMutableRefboxConfig();
        if (text == "Yellow")
        {
            refbox_config->mutableOverrideRefboxFriendlyTeamColor()->setValue(true);
            refbox_config->mutableFriendlyColorYellow()->setValue(true);
        }
        else if (text == "Blue")
        {
            refbox_config->mutableOverrideRefboxFriendlyTeamColor()->setValue(true);
            refbox_config->mutableFriendlyColorYellow()->setValue(false);
        }
        else if (text == "Use Refbox")
        {
            refbox_config->mutableOverrideRefboxFriendlyTeamColor()->setValue(false);
        }
        else
        {
            LOG(FATAL) << "Tried to set the team colour with an invalid value: '"
                       << text.toStdString() << "'" << std::endl;
        }
    };
    QWidget::connect(widget->team_colour_combo_box, &QComboBox::currentTextChanged,
                     on_team_colour_changed);
}

void setupGameStateOverrideComboBox(Ui::AutoGeneratedMainWidget *widget,
                                    std::shared_ptr<ThunderbotsConfig> config)
{
    // TODO: Set this up using factory values like the play override once a factory of
    // these values is available
    widget->gamestate_override_combo_box->insertItem(0, "None");
    widget->gamestate_override_combo_box->insertItem(1, "Play");
    widget->gamestate_override_combo_box->insertItem(2, "Halt");
    widget->gamestate_override_combo_box->insertItem(3, "Stop");

    auto on_gamestate_changed = [config](const QString &text) {
        auto refbox_config =
            config->getMutableAIControlConfig()->getMutableRefboxConfig();
        if (text == "Use Refbox")
        {
            refbox_config->mutableOverrideRefboxPlay()->setValue(false);
        }
        else
        {
            refbox_config->mutableOverrideRefboxPlay()->setValue(true);
            refbox_config->mutableCurrentRefboxPlay()->setValue(text.toStdString());
        }
    };
    QWidget::connect(widget->gamestate_override_combo_box, &QComboBox::currentTextChanged,
                     on_gamestate_changed);
}

void setupDefendingSideComboBox(Ui::AutoGeneratedMainWidget *widget,
                                std::shared_ptr<ThunderbotsConfig> config)
{
    // See issue #811 for getting these value from an enum / factory
    widget->defending_side_combo_box->insertItem(0, "Use Refbox");
    widget->defending_side_combo_box->insertItem(1, "East");
    widget->defending_side_combo_box->insertItem(2, "West");

    auto on_defending_side_changed = [config](const QString &text) {
        auto refbox_config =
            config->getMutableAIControlConfig()->getMutableRefboxConfig();
        if (text == "Use Refbox")
        {
            refbox_config->mutableOverrideRefboxDefendingSide()->setValue(false);
        }
        else if (text == "East")
        {
            refbox_config->mutableOverrideRefboxDefendingSide()->setValue(true);
            // TODO: Confirm how East and West map to positive and negative sides
            refbox_config->mutableDefendingPositiveSide()->setValue(false);
        }
        else if (text == "West")
        {
            config->getMutableAIControlConfig()->mutableOverrideAIPlay()->setValue(false);
            // TODO: Confirm how East and West map to positive and negative sides
            refbox_config->mutableDefendingPositiveSide()->setValue(true);
        }
        else
        {
            LOG(FATAL) << "Tried to set the defending side with an invalid value: '"
                       << text.toStdString() << "'" << std::endl;
        }
    };
    QWidget::connect(widget->defending_side_combo_box, &QComboBox::currentTextChanged,
                     on_defending_side_changed);
}

void setupPlayOverrideComboBox(Ui::AutoGeneratedMainWidget *widget,
                               std::shared_ptr<ThunderbotsConfig> config)
{
    auto play_names = GenericFactory<std::string, Play>::getRegisteredNames();

    // Sort the entries in alphabetical order from a-z
    std::sort(play_names.begin(), play_names.end());

    // Create a new list with all the play names converted to QStrings
    QList<QString> qt_play_names;
    std::transform(play_names.begin(), play_names.end(),
                   std::back_inserter(qt_play_names),
                   [](std::string name) { return QString::fromStdString(name); });

    widget->play_override_combo_box->insertItem(0, "Use AI Selection");
    widget->play_override_combo_box->insertItems(1, qt_play_names);

    auto on_play_changed = [config](const QString &text) {
        if (text == "Use AI Selection")
        {
            config->getMutableAIControlConfig()->mutableOverrideAIPlay()->setValue(false);
        }
        else
        {
            config->getMutableAIControlConfig()->mutableOverrideAIPlay()->setValue(true);
            config->getMutableAIControlConfig()->mutableCurrentAIPlay()->setValue(
                text.toStdString());
        }
    };
    QWidget::connect(widget->play_override_combo_box, &QComboBox::currentTextChanged,
                     on_play_changed);
}