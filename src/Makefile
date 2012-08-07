# don't use Verbose mode (be silent)?
ifeq (,$V)
MFLAGS+=-s
endif

.PHONY: all
all: release

.PHONY: debug
debug: PROFILE=debug
debug: make_gen copy_data
	@cd gen/$(PROFILE) && $(MAKE) $(MFLAGS) debug

.PHONY: release
release: PROFILE=release
release: make_gen copy_data
	@cd gen/$(PROFILE) && $(MAKE) $(MFLAGS) release

.PHONY: debug-flash
debug-flash: PROFILE=debug
debug-flash: debug
	@cd gen/$(PROFILE) && $(MAKE) $(MFLAGS) flash_mcu

.PHONY: release-flash
release-flash: PROFILE=release
release-flash: release
	@cd gen/$(PROFILE) && $(MAKE) $(MFLAGS) flash_mcu

.PHONY: make_gen
make_gen:
	@mkdir -p gen/$(PROFILE)

# NOTE: this is not being lazy - it appears that only ONE *.c file can be used...
.PHONY: copy_data
copy_data: make_gen
	@cp -uav Makefile.gen gen/$(PROFILE)/Makefile
	@cp -uav *.c *.h gen/$(PROFILE)/

.PHONY: clean
clean:
	@rm -frv gen/
