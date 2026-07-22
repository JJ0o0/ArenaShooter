#pragma once

#include <physics/shapes.hpp>

class Collision {
    public:
        static bool AABBxAABB(const AABB& a, const AABB& b);

        static bool SpherexSphere(const Sphere& a, const Sphere& b);
        static bool SpherexAABB(const Sphere& s, const AABB& b);
        static bool SpherexCapsule(const Sphere& s, const Capsule& b);

        static bool CapsulexCapsule(const Capsule& a, const Capsule& b);
        static bool CapsulexAABB(const Capsule& c, const AABB& b, glm::vec3& outPointOnSegment, glm::vec3& outPointOnBox);

        static bool Test(const CollisionShape& a, const CollisionShape& b);
    private:
        static void ClosestPointLinexLine(
            const glm::vec3& A1, const glm::vec3& B1,
            const glm::vec3& A2, const glm::vec3& B2,
            float& outA, float& outB, float& outC, float& outE, float& outF,
            float& outDenom,
            glm::vec3& outD1, glm::vec3& outD2,
            float& outS, float& outT
        );

        static bool ClosestPointSegmentxSegment(
            const glm::vec3& A1, const glm::vec3& B1,
            const glm::vec3& A2, const glm::vec3& B2,
            const float& radius1, const float& radius2
        );

        static glm::vec3 ClosestPointOnSegment(
            const glm::vec3& point,
            const glm::vec3& A, const glm::vec3& B
        );
};
