#include <physics/collision.hpp>

#include <glm/glm.hpp>
#include <algorithm>

void Collision::ClosestPointLinexLine(
    const glm::vec3& A1, const glm::vec3& B1,
    const glm::vec3& A2, const glm::vec3& B2,
    float& outA, float& outB, float& outC, float& outE, float& outF,
    float& outDenom,
    glm::vec3& outD1, glm::vec3& outD2,
    float& outS, float& outT
) {
    // Vetores de direção e o vetor R
    glm::vec3 d1 = B1 - A1;
    glm::vec3 d2 = B2 - A2;
    glm::vec3 r = A1 - A2;

    outD1 = d1;
    outD2 = d2;

    // Produtos Escalares
    float a = glm::dot(d1, d1);
    float e = glm::dot(d2, d2);
    float b = glm::dot(d1, d2);
    float c = glm::dot(d1, r);
    float f = glm::dot(d2, r);

    outA = a;
    outB = b;
    outC = c;
    outE = e;
    outF = f;

    // Resolvendo sistema 2x2
    float denom = (a * e) - (b * b);
    float s = ((b * f) - (c * e)) / denom;
    float t = ((a * f) - (b * c)) / denom;

    outDenom = denom;
    outS = s;
    outT = t;
}

bool Collision::ClosestPointSegmentxSegment(
    const glm::vec3& A1, const glm::vec3& B1,
    const glm::vec3& A2, const glm::vec3& B2,
    const float& radius1, const float& radius2
) {
    // Resolve como se fossem retas infinitas
    float a, b, c, e, f, denom, s, t;
    glm::vec3 d1, d2;
    ClosestPointLinexLine(
        A1, B1, A2, B2,
        a, b, c, e, f,
        denom,
        d1, d2,
        s, t
    );

    // Trata caso de retas paralelas (OBS: que porra é essa)
    if (denom < 1e-6f * a * e) {
        s = 0;
        t = ((b * s) + f) / e;
    }

    // Clampa s em (0, 1)
    float sClamped = std::clamp(s, 0.0f, 1.0f);

    if (sClamped != s) {
        t = ((b * sClamped) + f) / e;
        s = sClamped;
    }

    // Clampa t em (0, 1)
    float tClamped = std::clamp(t, 0.0f, 1.0f);

    if (tClamped != t) {
        s = ((b * tClamped) - c) / a;
        t = tClamped;

        // Clampa s mais uma vez por segurança
        s = std::clamp(s, 0.0f, 1.0f);
    }

    glm::vec3 p = A1 + (s * d1);
    glm::vec3 q = A2 + (t * d2);
    glm::vec3 diff = p - q;

    float D2 = glm::dot(diff, diff);
    float radiusSum = radius1 + radius2;

    return D2 < (radiusSum * radiusSum);
}

glm::vec3 Collision::ClosestPointOnSegment(
    const glm::vec3& point,
    const glm::vec3& A, const glm::vec3& B
) {
    glm::vec3 segDirection = B - A;
    float t = glm::dot(point - A, segDirection) / glm::dot(segDirection, segDirection);
    t = std::clamp(t, 0.0f, 1.0f);

    glm::vec3 closest = A + (t * segDirection);

    return closest;
}

bool Collision::AABBxAABB(const AABB &a, const AABB &b) {
    return
        (a.Min.x <= b.Max.x && b.Min.x <= a.Max.x) &&
        (a.Min.y <= b.Max.y && b.Min.y <= a.Max.y) &&
        (a.Min.z <= b.Max.z && b.Min.z <= a.Max.z);
}

bool Collision::SpherexSphere(const Sphere &a, const Sphere &b) {
    glm::vec3 diff = b.Center - a.Center;
    float d2 = glm::dot(diff, diff);
    float radiusSum = a.Radius + b.Radius;

    return d2 < (radiusSum * radiusSum);
}

bool Collision::SpherexAABB(const Sphere &s, const AABB &b) {
    glm::vec3 closest = glm::clamp(s.Center, b.Min, b.Max);
    glm::vec3 diff = s.Center - closest;
    float d2 = glm::dot(diff, diff);

    return d2 < (s.Radius * s.Radius);
}

bool Collision::CapsulexCapsule(const Capsule &a, const Capsule &b) {
    return ClosestPointSegmentxSegment(a.A, a.B, b.A, b.B, a.Radius, b.Radius);
}

bool Collision::CapsulexAABB(const Capsule &c, const AABB &b, glm::vec3& outPointOnSegment, glm::vec3& outPointOnBox) {
    glm::vec3 pointOnSegment = c.A + 0.5f * (c.B - c.A);
    glm::vec3 pointOnBox{0.0f};

    // Projeção alternada
    for (int i = 0; i < 3; i++) {
        pointOnBox = glm::clamp(pointOnSegment, b.Min, b.Max);
        pointOnSegment = ClosestPointOnSegment(pointOnBox, c.A, c.B);
    }

    outPointOnSegment = pointOnSegment;
    outPointOnBox = pointOnBox;

    glm::vec3 diff = pointOnSegment - pointOnBox;
    float d2 = glm::dot(diff, diff);

    return d2 < (c.Radius * c.Radius);
}
