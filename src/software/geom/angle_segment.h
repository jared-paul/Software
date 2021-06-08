#pragma once

#include "software/geom/angle.h"

class AngleSegment
{
   public:
    /**
     * Constructs an AngleSegment represented by a top angle and bottom angle
     *
     * @param angle_top the most positive angle
     * @param angle_bottom the most negative angle
     */
    explicit AngleSegment(Angle angle_top, Angle angle_bottom);

    /**
     * Gets the top (most positive) angle of the angle segment
     *
     * @return the top angle of the angle segment
     */
    const Angle &getAngleTop() const;

    /**
     * Sets the top (most positive) angle of the angle segment
     *
     * @param angle_top the top angle of the angle segment
     */
    void setAngleTop(const Angle &angle_top);

    /**
     * Gets the bottom (most negative) angle of the angle segment
     *
     * @return the bottom angle of the angle segment
     */
    const Angle &getAngleBottom() const;

    /**
     * Sets the bottom (most negative) angle of the angle segment
     *
     * @param angle_bottom the bottom angle of the angle segment
     */
    void setAngleBottom(const Angle &angle_bottom);


    /**
     * Gets the abs delta between the two angles that describe this angle segment
     *
     * @return the abs delta between the top and bottom angles
     */
    double getDelta() const;

    /**
     * Compares another AngleSegment's top angle
     * Used to make sorting more performant
     *
     * @param other the other AngleSegment to compare to
     * @return true if both AngleSegment's top angles are equal
     */
    bool operator==(const AngleSegment &other) const;

    /**
     * Compares another AngleSegment's top angle
     * Used to make sorting more performant
     *
     * @param other the other AngleSegment to compare to
     * @return true if this top angle is less than the other's top angle
     */
    bool operator<(const AngleSegment &other) const;

    /**
     * Compares another AngleSegment's top angle
     * Used to make sorting more performant
     *
     * @param other the other AngleSegment to compare to
     * @return true if this top angle is greater than the other's top angle
     */
    bool operator>(const AngleSegment &other) const;

   private:
    Angle angle_top_;
    Angle angle_bottom_;
};