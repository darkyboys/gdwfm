# **Goblin's Demonic Web File Manager (GDWFM)**
<img src="art/banner - light.png"> 
A free, open-source, theme-able, lightweight web-based file manager and server written in C++, powered by a custom-maintained fork of `cpp-httplib`.

---

## 📌 **Overview**

**GDWFM (Goblin’s Demonic Web File Manager)** is a tiny but powerful local web server and browser-based file manager.

It allows you to:

* Host any directory as a navigable UI over HTTP
* Browse folders through a clean, responsive HTML frontend
* Download files directly
* Extend or modify the entire backend (MIT License)
* Customize the appearance through themes in `~/.config/gdwfm/`

GDWFM uses a **custom-maintained fork** of `cpp-httplib` (Yuji Hirose), and **all issues related to the web server should be reported to the GDWFM project**, not the official httplib repo.

---

## ✨ **Features**

* 🌐 Serves any folder over HTTP
* 📁 Auto-generated interactive file manager UI
* 🖼️ Clean and responsive default theme
* 🎨 Theme system (stored entirely in `~/.config/gdwfm/`)
* 📄 Supports HTML, CSS, JS, images, and raw files
* ⚙️ Configurable host, port, and root directory
* 🛠️ No dependencies — compiled with your **Cook** build system
* 🧵 Uses standard C++ (`<filesystem>`, `<fstream>`, `<iostream>`)
* 🚫 No external libraries required

---

## ⚙️ **Command Line Options**

| Flag                         | Description                           |
| ---------------------------- | ------------------------------------- |
| `-v`, `--version`            | Show GDWFM version                    |
| `-p <port>`, `--port <port>` | Set HTTP server port                  |
| `-r <path>`, `--root <path>` | Set root directory to serve           |
| `-h <host>`, `--host <host>` | Set host address (default: `0.0.0.0`) |

Example:

```bash
./gdwfm --port 9090 --root ~/Documents
```

---

## 🧑‍💻 **Build Instructions**

GDWFM uses your clean, dependency-free **Cook build system**.

```bash
git clone https://github.com/darkyboys/gdwfm
cd gdwfm/src
cook -d
```

✔️ The executable is placed directly in `src/`.
✔️ No config files needed.

---

## 🔃 **Installation**

GDWFM installs into `/usr/local/bin/`, which requires root privileges.

Install:

```bash
sudo cook install
```

Install only the default theme:

```bash
cook install/theme
```

This installs:

```
~/.config/gdwfm/
    index.html
    ui.html
    android.button.js
    icon/
```

The server automatically copies these on startup.

---

## 🎨 **Themes**

Themes live entirely inside:

```
~/.config/gdwfm/
```

Anything you change there (HTML, CSS, JS, icons) becomes your custom UI.

You can customize:

* `ui.html` (main file explorer template)
* `android.button.js` (mobile ripple effects)
* Icons in:

  ```
  ~/.config/gdwfm/icon/
  ```

A corrupted or missing theme triggers an error message with instructions to reinstall.

---

## 🖥️ **Default UI Features**

The included default theme provides:

* A navigation bar
* Path input and navigation button
* File and folder listing
* Download buttons
* Mobile-ready ripple animations
* Clean light gray aesthetic
* Simple and fast UX

<img width="1920" height="924" alt="Screenshot_20251115_121335" src="https://github.com/user-attachments/assets/f3f85bfb-34ff-488b-9d35-609673ecbd84" />

---

## 📁 **Key Internal Paths**

| Path                          | Purpose                   |
| ----------------------------- | ------------------------- |
| `~/.config/gdwfm/`            | User theme directory      |
| `/.gdwfm-server/config/`      | Server-side copy of theme |
| `/.gdwfm-server/config/icon/` | Icons used by UI          |

These are recreated when the server starts if necessary.

---

## 🧱 **Technical Notes**

* Written in **C++17+**
* Embedded file detection for MIME types
* Automatically generates HTML from directory contents
* Lightweight use of `httplib::Server`
* Minimal system calls to mirror theme files into server space
* Fully extensible backend — modify as you wish

---

## 📜 **License**

GDWFM is licensed under the **MIT License**.
You are free to modify, redistribute, and build on top of it.

---

## 🐛 **Issues & Bug Reports**

All issues related to GDWFM and its custom httplib fork should be reported here:

👉 **[https://github.com/daryboys/gdwfm/issues](https://github.com/darkyboys/gdwfm/issues)**

---

## 🙌 **Acknowledgements**

* **cpp-httplib** by Yuji Hirose (custom fork maintained by the GDWFM Project)
* Development by **ghgltggamer**
