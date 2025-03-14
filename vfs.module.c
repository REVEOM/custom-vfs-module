#include <linux/module.h>
#include <linux/fs.h>
#include <linux/init.h>
#include <linux/namei.h>
#include <linux/slab.h>
#include <linux/uaccess.h> // Kullanıcı verilerine erişim için

#define MYFS_NAME "myvfs"
#define TEST_FILE_CONTENT "Hello from MyVFS!\n"

static struct dentry *myfs_mount(struct file_system_type *fs_type, int flags,
                                 const char *dev_name, void *data);

static struct file_operations myfs_file_ops = {
    .read = simple_read_from_buffer,
};

static ssize_t myfs_read(struct file *file, char __user *buf, size_t len, loff_t *offset) {
    return simple_read_from_buffer(buf, len, offset, TEST_FILE_CONTENT, strlen(TEST_FILE_CONTENT));
}

static struct file_system_type myfs_type = {
    .owner = THIS_MODULE,
    .name = MYFS_NAME,
    .mount = myfs_mount,
    .kill_sb = kill_litter_super,
};

static struct dentry *myfs_mount(struct file_system_type *fs_type, int flags,
                                 const char *dev_name, void *data) {
    struct dentry *entry = mount_nodev(fs_type, flags, data, simple_fill_super);
    if (IS_ERR(entry)) {
        printk(KERN_ERR "Failed to mount myvfs.\n");
    } else {
        printk(KERN_INFO "myvfs mounted successfully.\n");
    }
    return entry;
}

static int __init myfs_init(void) {
    int ret = register_filesystem(&myfs_type);
    if (ret == 0) {
        printk(KERN_INFO "myvfs registered successfully.\n");
    } else {
        printk(KERN_ERR "Failed to register myvfs.\n");
    }
    return ret;
}

static void __exit myfs_exit(void) {
    int ret = unregister_filesystem(&myfs_type);
    if (ret == 0) {
        printk(KERN_INFO "myvfs unregistered successfully.\n");
    } else {
        printk(KERN_ERR "Failed to unregister myvfs.\n");
    }
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Muhammet");
MODULE_DESCRIPTION("Advanced Virtual File System Kernel Module with Basic Read Capability");

module_init(myfs_init);
module_exit(myfs_exit);
