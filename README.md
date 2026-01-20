<p align="center">
  <img src="https://github.com/xSilverWasHere/42-project-badges/blob/main/covers/cover-minitalk.png" alt="MINITALK"/>
</p>

## 🛰️ Minitalk – Signal‑Based Client/Server Communication

Minitalk is a 42 School project that implements a simple client/server communication system in C using only Unix signals. It sends messages from a client process to a server process bit by bit using SIGUSR1 and SIGUSR2.​

## 📚 Project Overview

Objective:
Implement a small messaging protocol where a client encodes characters into bits and sends them to a server via Unix signals, which then decodes and prints the message.​

Language: C

Deliverable:
Two executables:

  ``server: Receives, reconstructs, and prints messages.``
  
  ``client: Sends a string message to the server using signals.``
    ​

## 📦 Contents

## ✅ Mandatory Part

The project is split into two main programs:

# 🛰️ Server

  Sets up signal handlers using sigaction with SA_SIGINFO to receive SIGUSR1 and SIGUSR2.

  Reconstructs each character bit by bit with a static current_char and bit_index, printing the message once a full character (8 bits) is received.​

  Shows its PID on startup so clients know where to send messages.​

# 📨 Client

  Encodes each character of the message into bits and sends them as SIGUSR1/SIGUSR2 to the server.

  Sends a terminating '\0' character to indicate the end of the message, allowing the server to print a newline.​

  Receives an acknowledgement signal from the server after each bit or character (depending on your implementation) to ensure reliable delivery.​

# 🧰 Shared Components

  Header: minitalk.h defines shared includes, macros (like PID_MAX), and links to your libft for utilities such as ft_printf and ft_bzero.​

## ⚙️ Build & Usage

Typical compilation (adjust src paths as needed):

# Compile server
``cc -Wall -Wextra -Werror server.c libft/libft.a -o server``

# Compile client
``cc -Wall -Wextra -Werror client.c libft/libft.a -o client``

Run the server:

``./server``
# Output example:
# Server PID: 12345

Run the client (in another terminal):

``./client 12345 "Hello from Minitalk!"``

The server will print the received message character by character as it reconstructs it from signals.​

## 🎯 What I Learned

This project deepened understanding of:

  Unix signals: Using SIGUSR1, SIGUSR2, and sigaction with siginfo_t for inter‑process communication.​

  Bitwise operations: Shifting and masking bits to encode and decode characters over a signal-only channel.​

  Process control: Working with kill, getpid, and synchronization between client and server using acknowledgements.​

  Robust C design: Structuring a small protocol, managing state with static variables, and integrating with a custom libft for cleaner and reusable utilities.
