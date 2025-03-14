# Custom Virtual File System Kernel Module

A kernel module for experimenting with Virtual File Systems (VFS) in Linux. This module demonstrates the basics of creating and registering a custom filesystem within the Linux kernel.

## Features
- Registers a custom virtual file system (`myvfs`).
- Supports mounting and unmounting operations.
- Provides a basic implementation of file read operations.
- Includes a simple virtual file with sample content.

## Requirements
- Linux Kernel (version 5.x or later recommended).
- GCC compiler and make utility installed.

## Installation
1. Clone this repository:
   ```bash
   git clone https://github.com/REVEOM/custom-vfs-module.git
   cd custom-vfs-module
