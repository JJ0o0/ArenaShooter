#pragma once

#include <stduuid/uuid.h>

class UUID {
    public:
        UUID() : m_uuid(Generate()) {}

        std::string ToString() const { return uuids::to_string(m_uuid); }
    private:
        static inline uuids::uuid Generate() {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static uuids::uuid_random_generator generator(gen);

            return generator();
        }

        uuids::uuid m_uuid;
};
