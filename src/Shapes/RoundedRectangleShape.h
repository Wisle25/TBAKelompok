#pragma once

#include "Core.h"

namespace sf
{
////////////////////////////////////////////////////////////
/// \brief Specialized shape representing a rectangle
/// with rounded corners
////////////////////////////////////////////////////////////
class RoundedRectangleShape : public sf::Shape
{
    public:
        ////////////////////////////////////////////////////////////
        /// \brief Default constructor
        ///
        /// \param size Size of the rectangle
        /// \param radius Radius for each rounded corner
        /// \param cornerPointCount Number of points of each corner
        ///
        ////////////////////////////////////////////////////////////
        explicit RoundedRectangleShape(const Vector2f& size = Vector2f(0, 0), float radius = 0, uint32_t cornerPointCount = 0);

        ////////////////////////////////////////////////////////////
        /// \brief Set the size of the rounded rectangle
        ///
        /// \param size New size of the rounded rectangle
        ///
        /// \see getSize
        ///
        ////////////////////////////////////////////////////////////
        void setSize(const Vector2f& size);

        ////////////////////////////////////////////////////////////
        /// \brief Get the size of the rounded rectangle
        ///
        /// \return Size of the rounded rectangle
        ///
        /// \see setSize
        ///
        ////////////////////////////////////////////////////////////
        const Vector2f& getSize() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the radius of the rounded corners
        ///
        /// \param radius Radius of the rounded corners
        ///
        /// \see getCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        void setCornersRadius(float radius);

        ////////////////////////////////////////////////////////////
        /// \brief Get the radius of the rounded corners
        ///
        /// \return Radius of the rounded corners
        ///
        /// \see setCornersRadius
        ///
        ////////////////////////////////////////////////////////////
        float getCornersRadius() const;

        ////////////////////////////////////////////////////////////
        /// \brief Set the number of points of each corner
        ///
        /// \param count New number of points of the rounded rectangle
        ///
        /// \see getPointCount
        ///
        ////////////////////////////////////////////////////////////
        void setCornerPointCount(uint32_t count);

        ////////////////////////////////////////////////////////////
        /// \brief Get the number of points defining the rounded rectangle
        ///
        /// \return Number of points of the rounded rectangle
        ///
        ////////////////////////////////////////////////////////////
        virtual std::size_t getPointCount() const;

        ////////////////////////////////////////////////////////////
        /// \brief Get a point of the rounded rectangle
        ///
        /// The result is undefined if \a index is out of the valid range.
        ///
        /// \param index Index of the point to get, in range [0 .. GetPointCount() - 1]
        ///
        /// \return Index-th point of the shape
        ///
        ////////////////////////////////////////////////////////////
        virtual sf::Vector2f getPoint(std::size_t index) const;

    private:
         ////////////////////////////////////////////////////////////
        // Member data
        ////////////////////////////////////////////////////////////
        Vector2f mySize;
        float myRadius;
        uint32_t myCornerPointCount;
};
}