# 👹 Goblin’s Demonic Tiny Web Server (GDTWS)
<img src="art/banner - light.png"> 
**GDTWS** — the *Goblin’s Demonic Tiny Web Server* — is a **blazing-fast**, single-binary HTTP file server written in **C++**, powered by [`cpp-httplib`](https://github.com/yhirose/cpp-httplib) and built with the [`cook`](https://github.com/darkyboys/cook) build system.

It’s small, fast, and unreasonably aggressive at serving your files.  
Perfect for local web development, embedded devices, or if you just like to summon demons with sockets. 🧙‍♂️🔥

---

## ⚙️ Features

- 🧩 **Zero dependencies** — no external libraries, no bloat.
- ⚡ **Native speed** — pure C++, compiled straight to machine code.
- 📂 **Static file hosting** — serves `.html`, `.css`, `.js`, images, and more.
- 🚫 **Secure** — prevents path traversal (no `../` hacks allowed).
- 🧠 **UTF-8 aware** — serves Unicode and emoji content properly.
- 💀 **Funny 404 messages** — each one cursed with a random demonic flavor.
- 🧰 **CLI support** — configurable port and root directory.
- 🧵 *(optional)* Multi-thread ready — built on top of cpp-httplib’s threaded model.

---

## 🧑‍💻 Build Instructions

This project uses the [**Cook**](https://github.com/darkyboys/cook) build system — a simple, clean, dependency-free build tool.

### 🔨 To build:
```bash
git clone https://github.com/darkyboys/gdtws
cd gdtws/src
cook -d
```

This will compile the binary directly (no configuration needed).
Your executable will appear in the same directory.

---

## 🔃 Install Instructions

Once you have builded the project it's time to install it. This will ask you for your root password but don't worry it's all safe, The root password is only required because the installer will try to move the binary to `/usr/local/bin` directory, Which without the root access isn't possible.

### 🔨 To install:
```bash
sudo cook install # Only for installation
cook install/theme # Just installing the theme
```

This will install the binary directly (no configuration needed).
This will also install the theme!

---

## 🚀 Usage

```bash
./gdtws [options]
```

### Available Options

| Option                       | Description                                          |
| ---------------------------- | ---------------------------------------------------- |
| `--port <n>` or `-p <n>`     | Set the port number (default: `8080`)                |
| `--root <dir>` or `-r <dir>` | Set the directory to serve files from (default: `.`) |
| `--version` or `-v`          | Show version info and exit                           |

### Example

Serve your `website/` folder on port `9000`:

```bash
./gdtws --port 9000 --root website
```

Output:

```
🚀 Goblin's Demonic Tiny Web Server v0.1.0 🧙‍♂️
📂 Root directory: /home/user/website
🌐 Server started on: http://0.0.0.0:9000
```

Then open your browser and visit:

```
http://localhost:9000
```

---

## 💀 Error Pages

When a file isn’t found, you’ll get one of GDTWS’s signature 404s, like:

> 💣 **Segmentation fault (core dumped) – 404 edition.**

They’re rendered as HTML, so you can proudly cry in style.

---

## 🧩 Embedding / Extending

Feel free to:

* Use this as a **backend base** for small apps.
* Embed it in your own project.
* Fork and modify it to your liking.

The code is heavily commented and easy to extend — add your own routes, hooks, or middleware.

---

## 🔐 Security Notes

* GDTWS automatically prevents access outside the root directory.
* URL patterns like `/../`, `//`, or other traversal attempts are blocked with a **403 Forbidden** page.
* All file reads are sandboxed inside the `--root` directory.

---

## 🧙‍♂️ License

This project is licensed under the **MIT License** — see [`LICENSE`](./LICENSE) for details.

---

## 🌌 Credits

* Written by **[ghgltggamer](https://github.com/darkyboys)**
* Built with **[cook](https://github.com/darkyboys/cook)**
* Powered by **[`cpp-httplib`](https://github.com/yhirose/cpp-httplib)** (Yuji Hirose)
* Managed under the **GDTWS Project**

---

> *"Sometimes the smallest server is the most demonic one."* 👹