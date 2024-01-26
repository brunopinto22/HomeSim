<img align="right" src="icon.ico" width="200" alt="Project Logo">

# HomeSim
Terminal Based **Smart Home Simulator** made in [C++](https://cplusplus.com) and [PDcurses](https://pdcurses.org) for the User Interface.

<img alt="GitHub Language Count" src="https://img.shields.io/github/languages/count/brunopinto22/HomeSim" /> <img alt="" src="https://img.shields.io/github/repo-size/brunopinto22/HomeSim" /> <img alt="GitHub Last Commit" src="https://img.shields.io/github/last-commit/brunopinto22/HomeSim" />

<br>

## Features 📑
**Smart Home simulation controlled by interconnected home automation components.**

The simulator includes **Zones** within the **Home**, each with Properties such as *temperature*, *light*, *etc*. These **Properties** are monitored by **Sensors**, feeding data to **Processors** that will take actions based on **Rules** determined by the user and the *readings*.

The simulator is controlled by commands written by the user.

<br>

## How to Use 🛠
You'll need **PDcurses** installed on your system and to configure **CLion**

* **PDcurses** : 
[https://github.com/wmcbrine/PDCurses/releases](https://github.com/wmcbrine/PDCurses/releases)

* **CLion Configuration** : [POO - 2324 - Biblioteca POO Consola - INSTRUCOES](/docs/POO%20-%202324%20-%20Biblioteca%20POO%20Consola%20-%20INSTRUCOES.pdf)

<br>

## Commands 💻
> `<xxx>` refers to a value (number or text), and the characters < and > are not part of what should be written.<br>
`<x | y | z>` indicates that only one of x, y, or z should be specified (again, without the <>).<br>
`[v]` indicates that the parameter v is optional, and the characters [ and ] should not be written.

<br>

* `prox` : Advance 1 moment, triggering the effects of components that react to the passage of time

* `avanca <n>` :  Advance *n* moments
  
* `hnova <num of lines> <num of columns>` : Creates a **Home** with the indicated size
  
* `hrem` : Deletes the **Home** 
  
* `znova <x> <y>` : Creates a new **Zone** on the indicated coordinates
  
* `zrem <Zone ID>` : Deletes a **Zone** based on its *ID*
  
* `zlista` : Lists all the **Zones** of the **Home**
  
* `zcomp <Zone ID>` : Lists all the **Components** of a **Zone**
  
* `zprops <Zone ID>` : Lists all the **Components** of a **Zone**
  
* `pmod <Zone ID> <name> <value>` : List all the **Properties** of a **Zone**
  
* `cnovo <Zone ID> <s | p | a> <type | command>` : List all the **Properties** of a **Zone**
  
* `crem <Zone ID> <s | p | a> <Component ID>` : Removes a **Component** from a **Zone**
  
* `rnova <Zone ID> <Processor ID> <rule type> <Sensor ID> [par1] [par2] [..]` : Adds a **Rule**, associated to a **Sensor**, to a **Processor**

* `pmuda <Zone ID> <Processor ID> <new command>` : Changes the command sent by the **Processor**
  
* `rlista <Zone ID> <Processor ID>` : Lists all the **Rules** of a **Processor**
  
* `rrem <Zone ID> <Processor ID> <Rule ID>` : Removes a **Rules** from a **Processor**
  
* `asoc <Zone ID> <Processor ID> <Component ID>` : Associates the output of a **Processor** with the specified **Component**
  
* `ades <Zone ID> <Processor ID> <Component ID>` : Disassociates the specified **Component** from the **Processor**
  
* `acom <Zone ID> <Processor ID> <command>` : Manually sends the specified command to the **Component**
  
* `psalva <Zone ID> <Processor ID> <name>` : Saves the state of a **Processor** and everything associated with it in memory with a given name
  
* `prepoe <name>` : Restores the previously saved **Processor** from memory with the specified name
  
* `prem <name>` : Deletes a copy of the **Processor** stored in memory
  
* `plista` : Lists all the saved copies of **Processors** stored in memory
  
* `exec <file name.txt>` : Executes all the commands in a given **text file**

> in the [tests](/tests/) folder there are some .txt files that show how the files should be, and can be ran by the Simulator

* `help` : Lists all the commands
  
* `sair` : Closes the program

<br>

## Documents 📁

* [Relatório](/docs/Relatório.pdf)

* [POO - 2324 - Enunciado Trabalho Pratico](/docs/POO%20-%202324%20-%20Enunciado%20Trabalho%20Pratico.pdf)
