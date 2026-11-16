# 🗳️ UoEm Student Union E-Voting System

A secure, console-based electronic voting system implemented in **C** for the University of Embu (UoEm) Student Council elections. Designed to ensure election integrity with built-in voter verification, duplicate vote prevention, dynamic candidate registration, and administrative reporting tools.

---

## ✨ Key Features

- **🔐 Voter Verification & Security:** Automatically registers and tracks student IDs (e.g., `D33/1234/2024`) to prevent multiple voting.
- **👥 Candidate Management:** Pre-configured with student council positions (President, Secretary General) with admin options to dynamically register new candidates.
- **📊 Live Results & Tallying:** Real-time vote counting and secure display of candidate standings.
- **📁 CSV Results Export:** Admin feature to export complete election results directly into a `.csv` file for external auditing and spreadsheet analysis (Excel/Google Sheets).
- **🛡️ Robust Input Handling:** Guards against invalid menu selections and input buffer overflows.

---

## 🛠️ Tech Stack

- **Language:** C (Standard C99/C11)
- **Data Structures:** Structs, Arrays, Dynamic Count Tracking
- **File I/O:** Standard Input/Output (`stdio.h`), File Streams (`fopen`, `fprintf`)

---

## 🚀 Getting Started

### Prerequisites
You need a C compiler installed on your system (such as GCC on Linux/WSL or MinGW on Windows).

### Compilation & Execution
1. Clone the repository or download the source code:
   ```bash
   git clone [https://github.com/YOUR_USERNAME/UoEm-E-Voting-System.git](https://github.com/YOUR_USERNAME/UoEm-E-Voting-System.git)
   cd UoEm-E-Voting-System
