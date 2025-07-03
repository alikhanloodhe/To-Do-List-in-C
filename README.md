# 📋 Daily Task Manager and Reminder (FOCP Project)

A C-based **console application** that helps you manage your daily tasks and set reminders efficiently. Designed to boost productivity with features like task editing, reminders, and completed task tracking.

---

## 🛠 Features

- ✅ Add new tasks
- ⏰ Set reminders (today, tomorrow, or custom date)
- 📋 View all pending tasks
- ✏️ Edit existing tasks
- ❌ Remove tasks
- ✔️ Mark tasks as completed
- 📂 View completed tasks
- 💾 Persistent task storage (tasks saved in `.txt` files)

---

## 📁 File Structure

| File             | Purpose                                  |
|------------------|-------------------------------------------|
| `main.c`         | Main source code file                     |
| `text.txt`       | Stores **pending tasks**                 |
| `complete.txt`   | Stores **completed tasks**               |

---

## 🧠 How It Works

- Tasks are stored in a 2D array and persisted to files (`text.txt` and `complete.txt`).
- You can set reminders using system time (`<time.h>`) and format them with `strftime`.
- The app checks for overdue tasks and flags them.
- Reminders are embedded in task strings using a special format:  
  `(Reminder: YYYY-MM-DD HH:MM:SS)`

---

## 📦 Dependencies

This project uses standard C libraries:

- `<stdio.h>` – File I/O
- `<stdlib.h>` – General utilities
- `<string.h>` – String handling
- `<time.h>` – Date/time operations
- `<windows.h>` – For `Sleep()` (Windows only)
- `<conio.h>` – Console I/O (Windows only)

> ⚠️ This code is Windows-specific. To port it to Linux or macOS, replace `Sleep()` and remove `<windows.h>` and `<conio.h>`.

---

## 🚀 Getting Started

### ✅ Run on Windows

1. Compile:
    ```bash
    gcc main.c -o task_manager
    ```

2. Run:
    ```bash
    ./task_manager
    ```

3. Follow the on-screen menu.

---

## 🧪 Sample Use

Menu:

Add Task

Set reminder

Display To-Do List

Edit Task

Remove Task

Mark Task as Completed

Show Completed Tasks

Exit
---

## 📌 Notes

- Maximum task limit is **100**.
- Tasks and reminders are stored as plain text.
- Reminder time must be in **24-hour format**.

---

## 🙌 Acknowledgements

Project for **Fundamentals of Computer Programming (FOCP)** course.

> *"Be disciplined and boost your dopamine upon completion of a task."*

---

## 📜 License

This project is for academic purposes. Feel free to modify and use it as a learning resource.

---
