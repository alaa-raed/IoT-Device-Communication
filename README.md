# IoT Device Communication System

This project demonstrates network communication for IoT devices using both **TCP (Transmission Control Protocol)** and **UDP (User Datagram Protocol)**. It leverages **Object-Oriented Programming (OOP)** principles and the **Factory Design Pattern** to build a flexible, modular, and scalable communication framework.

---

## 🚀 Features
- **Unicast TCP Communication**: One-to-one communication for reliable data transfer.
- **Multicast UDP Communication**: One-to-many communication for lightweight, high-speed messaging.
- **Object-Oriented Design**:
  - Inheritance, polymorphism, and encapsulation for modularity and maintainability.
- **Factory Pattern**:
  - Simplifies socket and channel creation while ensuring extensibility.
- **Reusable Components**:
  - Server and Client channel abstractions for both TCP and UDP.
- **Cross-Terminal Execution**:
  - Works on Linux with Makefile-based builds.

---

## 🏗️ Project Structure
```
project/
├── Application/
│   ├── Makefile
│   ├── unicast/
│   │   └── unicast.mk
│   ├── multicast/
│   │   └── multicast.mk
│   └── out/
│       ├── gen/
│       └── lib/
└── module/
    ├── module.mk
    ├── inc/
    └── src/
```

---

## ⚙️ Build Instructions

### Build Both Applications
From the project root:
```bash
cd Application
make
```

### Clean Build Files
```bash
make clean
```

---

## ▶️ Running the Applications

### Unicast (TCP) Example
1. Start the TCP server:
   ```bash
   cd Application/unicast
   ./server_out
   ```
2. In another terminal, run the client:
   ```bash
   ./client_out
   ```

### Multicast (UDP) Example
1. Start the UDP multicast server:
   ```bash
   cd Application/multicast
   ./multicast_server_out
   ```
2. Run multiple clients:
   ```bash
   ./client1_out
   ./client2_out
   ```

---

## 📂 Class Overview

- **Socket (Interface)** → Base for all sockets.  
  - **TCPSocket**: Implements TCP unicast communication.  
  - **UDPSocket**: Implements UDP multicast communication.  

- **Channel (Interface)** → Base for communication channels.  
  - **ServerChannel**: Handles server logic.  
  - **ClientChannel**: Handles client logic.  

- **Factories**:  
  - `SocketFactory`: Creates TCP or UDP sockets.  
  - `ChannelFactory`: Creates Server or Client channels.

---

## 📐 Design Patterns
- **Factory Pattern**: Decouples object instantiation from usage, allowing new socket or channel types to be added with minimal changes.
- **OOP Principles**: Inheritance, polymorphism, and encapsulation ensure clean and maintainable architecture.

---

## 🛠️ Technologies Used
- **C++** (OOP, Design Patterns)
- **Linux** (Sockets, Networking)
- **Makefile** (Build Automation)

---

## 📜 License
This project is licensed under the MIT License — feel free to use, modify, and share.

---

## 🤝 Contributing
Contributions are welcome! Feel free to fork the repo and submit pull requests for enhancements or bug fixes.

---

## 📧 Contact
Developed by **Alaa Raed Saed**  
- 📩 [alaaraed00@gmail.com](mailto:alaaraed00@gmail.com)  
- 🌐 [LinkedIn](https://www.linkedin.com/in/alaa-raed-676a71202/)  
- 💻 [GitHub](https://github.com/alaa-raed)  
