BINARY_NAME = dp
SRC = main.c

CFLAGS = -Oz -s -ffunction-sections -fdata-sections -std=c23
LDFLAGS = -Wl,--gc-sections -Wl,--build-id=none

TARGETS = \
	x86_64-linux-musl \
	aarch64-linux-musl \
	x86_64-linux-gnu \
	aarch64-linux-gnu \
	x86_64-windows-gnu \
	aarch64-windows-gnu \
	x86_64-macos \
	aarch64-macos \
	x86_64-freebsd \
	x86_64-openbsd

.PHONY: all $(TARGETS)

all: $(TARGETS)

$(TARGETS):
	@echo "Building for $@..."
	@$(eval EXT := $(if $(findstring windows,$@),.exe,))
	@$(eval PLAT_FLAGS := $(if $(findstring windows,$@),-lm,-flto))
	@zig cc -target $@ $(CFLAGS) $(SRC) -o $(BINARY_NAME)-$@$(EXT) $(LDFLAGS)

