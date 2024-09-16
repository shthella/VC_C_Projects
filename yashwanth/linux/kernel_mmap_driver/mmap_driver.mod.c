#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif

static const struct modversion_info ____versions[]
__used __section(__versions) = {
	{ 0x6e5e9ea5, "module_layout" },
	{ 0xf147da98, "class_unregister" },
	{ 0x71b7020e, "device_destroy" },
	{ 0x201d0f70, "class_destroy" },
	{ 0xd20e521a, "device_create" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0xa640d12, "__class_create" },
	{ 0xe9e73cc4, "__register_chrdev" },
	{ 0x49ce5766, "remap_pfn_range" },
	{ 0xc5850110, "printk" },
	{ 0xbdfb6dbb, "__fentry__" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "03ECAF771A58103D2645FE2");