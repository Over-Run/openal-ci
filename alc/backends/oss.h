#ifndef BACKENDS_OSS_H
#define BACKENDS_OSS_H

#include "backends/base.h"

struct OSSBackendFactory final : public BackendFactory {
public:
    bool init() override;

    bool querySupport(BackendType type) override;

    std::string probe(DevProbe type) override;

    BackendPtr createBackend(ALCdevice *device, BackendType type) override;

    static BackendFactory &getFactory();
};

#endif /* BACKENDS_OSS_H */
