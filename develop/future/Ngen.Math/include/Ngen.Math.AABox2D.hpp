#ifndef _NGEN_MATH_AABOX2D
#define _NGEN_MATH_AABOX2D

#include "Ngen.Math.Vector2.hpp"
#include "Ngen.Math.Line2D.hpp"

namespace Ngen {
	namespace Math {


      enum class ECollisionKind {
         // Simple Collision Kind
         /// @brief No collision.
         NONE,
         /// @brief No collision.  However, the boundaries of the two structures are the minimum distance away from the other.
         OUTSIDE,
         /// @brief Collision.  The boundaries of the two structures are resting inside the same space.
         TOUCHING,
         /// @brief Collision.  The structure is inside the boundary of the other structure.
         INSIDE,
         /// @brief Collision. The other structure is inside the boundary of this structure.
         HOLDING,
          /// @brief Collision. The other structure is partially inside the boundary of this structure.
         CROSSING,
      };


      class CollisionResult2D {
      public:
         /// @brief The information gathered for the testing structure.
         ECollisionKind Lhs;

         /// @brief The information gathered for the structure being tested.
         ECollisionKind Rhs;

         /// @brief The smallest distance from each of the two points of collision.
         Line2D CollisonSpace;
      };

      class CollisionResult3D {
      public:
         /// @brief The information gathered for the testing structure.
         ECollisionKind Lhs;

         /// @brief The information gathered for the structure being tested.
         ECollisionKind Rhs;

         /// @brief The smallest distance from each of the two colliding points on each structures.
         Line3D CollisonSpace;
      };

		class AxisAlignedBox2D {
      private:
         // Fields
			Vector2 mTopLeft;
			Vector2 mBottomRight;

		public:
		   //Properties
		   Vector2 TopLeft() const { return Vector2(mTopLeft); }
		   void TopLeft(const Vector2& rhs) { mTopLeft = rhs; }

		   Vector2 TopRight() const { return Vector2(mBottomRight.X, mTopLeft.Y); }
		   void TopRight(const Vector2& rhs) { mBottomRight.X = rhs.X; mTopLeft.Y = rhs.Y; }

		   Vector2 BottomRight() const { return Vector2(mBottomRight); }
		   void BottomRight(const Vector2& rhs) { mBottomRight = rhs; }

		   Vector2 BottomLeft() const { return Vector2(mTopLeft.X, mBottomRight.Y); }
		   void BottomLeft(const Vector2& rhs) { mTopLeft.X = rhs.X; mBottomRight.Y = rhs.Y; }

         bool IsValid() const { return mTopLeft.X < mBottomRight.X && mTopLeft.Y > mBottomRight.Y; }

			//Init
         AxisAlignedBox2D () : mTopLeft(0), mBottomRight(0) {}
         AxisAlignedBox2D (const AxisAlignedBox2D& copy) : mTopLeft(copy.mTopLeft), mBottomRight(copy.mBottomRight) {}
         AxisAlignedBox2D (const Vector2& mTopLeft, const Vector2& mBottomRight) : mTopLeft(mTopLeft), mBottomRight(mBottomRight) {}
         AxisAlignedBox2D (const Vector2& mTopLeftmBottomRight) : mTopLeft(mTopLeftmBottomRight), mBottomRight(mTopLeftmBottomRight) {}

         //Operators
         bool operator==(const AxisAlignedBox2D& rhs) const {
            return mTopLeft == rhs.mTopLeft && mBottomRight == rhs.mBottomRight;
         }
         bool operator!=(const AxisAlignedBox2D& rhs) const {
            return mTopLeft != rhs.mTopLeft || mBottomRight != rhs.mBottomRight;
         }
         AxisAlignedBox2D& operator+=(const AxisAlignedBox2D& rhs) {
            mTopLeft.X = mTopLeft.X > rhs.mTopLeft.X ? rhs.mTopLeft.X : mTopLeft.X;
            mTopLeft.Y = mTopLeft.Y > rhs.mTopLeft.Y ? mTopLeft.Y : rhd.mTopLeft.Y;
            mBottomRight.X = mBottomRight.X > rhs.mBottomRight.X ? mBottomRight.X : rhs.mBottomRight.X;
            mBottomRight.Y = mBottomRight.Y < rhs.mBottomRight.Y ? mBottomRight.Y : rhs.mBottomRight.Y;
         }
          AxisAlignedBox2D operator+(const AxisAlignedBox2D& rhs) const {
             auto result = AxisAlignedBox2D(rhs);
             result += rhs;
             return result)
         }
         AxisAlignedBox2D& operator-=(const AxisAlignedBox2D& rhs) {
            mTopLeft.X = mTopLeft.X < rhs.mTopLeft.X ? rhs.mTopLeft.X : mTopLeft.X;
            mTopLeft.Y = mTopLeft.Y < rhs.mTopLeft.Y ? mTopLeft.Y : rhd.mTopLeft.Y;
            mBottomRight.X = mBottomRight.X < rhs.mBottomRight.X ? mBottomRight.X : rhs.mBottomRight.X;
            mBottomRight.Y = mBottomRight.Y > rhs.mBottomRight.Y ? mBottomRight.Y : rhs.mBottomRight.Y;
         }
          AxisAlignedBox2D operator-(const AxisAlignedBox2D& rhs) const {
             auto result = AxisAlignedBox2D(rhs);
             result -= rhs;
             return result)
         }

         // Methods
         CollisionResult2D CheckCollision(const Vector2& point) const {
            CollisionResult2D result;
            result.Lhs = result.Rhs = ECollisionKind::NONE;

            bool isHolding = (point.X > mTopLeft.X && point.Y < mTopLeft.Y && point.Y > mBottomRight.Y && point.Y < mBottomRight.X);
            bool isTouching = (point.X == mTopLeft.X && point.Y >= mBottomRight.Y && point.Y <= mTopLeft.Y) ||
                               (point.X == mBottomRight.X && point.Y >= mBottomRight.Y && point.Y <= mTopLeft.Y) ||
                               (point.Y == mTopLeft.Y && point.X >= mTopLeft.X && point.X <= mBottomRight.X) ||
                               (point.Y == mBottomRight.Y && point.X >= mTopLeft.X && point.X <= mBottomRight.X);

            if(isHolding) {
               result.Lhs = ECollisionKind::HOLDING;
               result.Rhs = ECollisionKind::INSIDE;
            } else if(isTouching) {
               result.Lhs = result.Rhs = ECollisionKind::TOUCHING;
            }

            return result;
         }
		};

		CollisionResult2D CheckCollision(const AxisAlignedBox2D& box) const {
            CollisionResult2D result;
            result.Lhs = result.Rhs = ECollisionKind::NONE;
            result.CollisonSpace = Line2D();

            auto bottom = CheckCollision(box.mBottomRight);
            auto top = CheckCollision(box.mTopLeft);

            bool isHolding = (top.Lhs == ECollisionKind::HOLDING || top.Lhs == ECollisionKind::TOUCHING) &&
                             (bottom.Lhs == ECollisionKind::HOLDING || bottom.Lhs == ECollisionKind::TOUCHING);

            bool isTouching = (box.mTopLeft - mTopLeft) == Vector2::Zero &&
                              (box.mBottomRight - mBottomRight) == Vector2::Zero;

            bool isCrossing =(top.Lhs == ECollisionKind::HOLDING || top.Lhs == ECollisionKind::TOUCHING) ||
                             (bottom.Lhs == ECollisionKind::HOLDING || bottom.Lhs == ECollisionKind::TOUCHING);


            if(isTouching) {
               result.Lhs = ECollisionKind::TOUCHING;
            } else if(isHolding) {
               result.Lhs = ECollisionKind::HOLDING;
               result.Rhs = ECollisionKind::INSIDE;
            } else if(isCrossing) {
               result.Lhs = ECollisionKind::CROSSING;
               result.Rhs = ECollisionKind::CROSSING;
            }

            return result;
         }
		};


		typedef AxisAlignedBox2D aabox2d;
	}
}
