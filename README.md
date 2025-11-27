<img src="readme/minishell.png" alt="minishell" width="900"/>

<div align="center">

# Minishell
### A Simplified Unix Shell Project at 42 School

[![Contributors][contributors-shield]][contributors-url]
[![Forks][forks-shield]][forks-url]
[![Stargazers][stars-shield]][stars-url]
[![Issues][issues-shield]][issues-url]
[![License][license-shield]][license-url]

</div>

---

## 🇬🇧 English

<details>
<summary><b>📖 Click to expand/collapse English version</b></summary>

### 📖 About

**Minishell** is a compulsory project for 42 School students. It consists of creating a simplified replica of a Unix shell in C that can interpret and execute commands, handle signals, pipes, redirections, environment variables, and built-in commands.

This project teaches:
- Command parsing and tokenization
- Process execution and management
- Signal handling (SIGINT, SIGQUIT, etc.)
- Pipe and redirection implementation
- Environment variable expansion
- Built-in command development
- Memory management and error handling

### 🧠 Skills Learned

By completing the Minishell project, students develop essential skills in C programming and system programming:

- **Command parsing**: Implementing a lexer and parser to handle shell syntax, quotes, and operators.
- **Process management**: Using fork, execve, waitpid for command execution and process control.
- **Signal handling**: Managing signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to mimic bash behavior.
- **Pipe implementation**: Creating pipelines between commands using pipe() and dup2().
- **Redirection handling**: Implementing input/output redirection (<, >, >>) and here-documents (<<).
- **Environment variables**: Expanding variables ($VAR) and managing the environment with builtins like export/unset.
- **Built-in commands**: Developing shell builtins (echo, cd, pwd, exit, env, export, unset) without forking.
- **Error handling**: Robust error management with appropriate exit codes and messages.
- **Code organization**: Structuring code into modular components, adhering to 42 norms for style and documentation.

## Approach
This project is quite extensive, with numerous specific cases to consider. The first challenge I encountered was wondering, "*Where do I start?*"<br>

I began Minishell two weeks before **Poid-lourd** could join me. During that time, I worked on the builtins and the initial parsing. Naturally, I had to create an execution base that **Poid-lourd** completely redid at the end of his two weeks. Over time, we quickly defined who should do what and how to do it.<br>

- **Poid-lourd**: Complete execution, redirections (<, <<, >>), and heredoc, which we more or less shared for ease.<br>

- **Me**: Complete parsing, builtins, signals.<br>

We managed error handling and everything else I haven't mentioned together to ensure a solid foundation and consistent logic. We quickly realized that our two real challenges would be parsing and execution due to the numerous specific cases in BASH.<br>

The project is very rewarding and allowed us to develop crucial skills in programming and collaboration. Working in a pair on such a complex project taught us how to communicate well, effectively distribute tasks, and overcome obstacles together.<br>

### **Features**

**Command history**: *Navigate through commands with up/down arrows.*<br>

**Pipes (|)**: *Chain commands to pass output from one to the next.*<br>

**Redirections**: *Input (<), output (>), append (>>), and here-doc (<<).*<br>

**Quote handling**: *Double quotes ("") and single quotes ('') escape special characters.*<br>

**Environment variables**: *Expand variables like $VAR in commands.*<br>

**Signal handling**: *Handle Ctrl+C, Ctrl+\, Ctrl+D like in bash.*<br>

**Built-ins**: *echo (-n), exit, env, export, unset, cd, pwd.*<br>

### **Features to be added:**

**Advanced expansions**: *More complex variable expansions and wildcards.*<br>

**Job control**: *Background processes and job management.*<br>

**Script mode**: *Support for executing shell scripts.*<br>

**Advanced builtins**: *More bash-like builtins and options.*<br>

### 📋 Table of Contents

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Compilation](#compilation)
- [Function Reference](#function-reference)
- [Credits](#credits)

<a name="features"></a>

### ✨ Features

- **Command execution** with absolute/relative paths and PATH resolution
- **Pipe support** for chaining multiple commands
- **Redirections** including input, output, append, and here-documents
- **Quote handling** for escaping special characters
- **Environment variable expansion** with proper quote handling
- **Signal management** mimicking bash behavior (Ctrl+C, Ctrl+\, Ctrl+D)
- **Built-in commands** (echo, cd, pwd, exit, env, export, unset)
- **Command history** with arrow key navigation
- **Strict C compliance** with 42 School norming standards

<a name="installation"></a>

### 🚀 Installation

```bash
# Clone the repository
git clone https://github.com/HaruSnak/42-minishell
cd 42-minishell
```

<a name="usage"></a>

### 💻 Usage

Compile and run the shell:

```bash
make
./minishell
```

Examples:
```bash
$ ls -la
$ echo "Hello World"
$ cat file.txt | grep "pattern" > output.txt
$ export VAR=value
$ $VAR
```

Controls:
- **Up/Down arrows**: Navigate command history
- **Ctrl+C**: Interrupt current command
- **Ctrl+D**: Exit shell (EOF)
- **Ctrl+\**: Quit with core dump

<a name="project-structure"></a>

### 📂 Project Structure

```
42-minishell/
├── Makefile                    # Build script
├── minishell.h                 # Main header file
├── minishell.c                 # Main shell entry point
├── LICENSE                     # License file
├── README.md                   # This file
├── README-Template.md          # Template for README
├── includes/
│   ├── exec.h
│   ├── minishell.h
│   └── libft/                  # Custom library
├── readme/                     # README assets
└── srcs/                       # Source files
    ├── builtins/               # Built-in commands
    ├── errors/                 # Error handling
    ├── execution/              # Command execution
    ├── parsing/                # Command parsing
    ├── redirections/           # I/O redirections
    ├── signals/                # Signal handling
    └── utils/                  # Utility functions
```

<a name="compilation"></a>

### 🔧 Compilation

Compile the project using the Makefile:

```bash
make          # Compile the shell
make clean    # Remove object files
make fclean   # Remove executable and object files
make re       # Recompile everything
```

<a name="function-reference"></a>

### 📚 Function Reference

#### Main Functions
- [`main`](srcs/minishell.c) - Shell initialization and main loop
- [`parse_input`](srcs/parsing/) - Command parsing and tokenization
- [`execute_command`](srcs/execution/) - Command execution logic
- [`handle_signals`](srcs/signals/) - Signal handling setup

#### Key Features
- **Parsing**: Tokenizes input, handles quotes and operators
- **Execution**: Forks processes, manages pipes and redirections
- **Builtins**: Implements shell built-in commands
- **Environment**: Manages environment variables and expansion

### 👨‍🎓 Note
<p align="left">
    <img width="201" height="169" alt="Image" src="https://github.com/user-attachments/assets/1e15fd1d-f7c7-4d97-b04a-468e342e1977" />
</p>

<a name="credits"></a>

### 📖 Credits

- **42 School Norm**: [Official C Coding Standard](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- **GNU Bash Manual**: [Bash Reference Manual](https://www.gnu.org/software/bash/manual/bash.html)
- **Readline Library**: For command line editing and history

### 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

</details>

---

## 🇫🇷 Français

<details>
<summary><b>📖 Cliquez pour développer/réduire la version française</b></summary>

### 📖 À propos

**Minishell** est un projet obligatoire pour les étudiants de l'école 42. Il s'agit de créer une réplique simplifiée d'un shell Unix en C capable d'interpréter et d'exécuter des commandes, de gérer les signaux, les pipes, les redirections et les variables d'environnement.

Ce projet enseigne :
- Le parsing et la tokenisation des commandes
- L'exécution et la gestion des processus
- La gestion des signaux (SIGINT, SIGQUIT, etc.)
- L'implémentation des pipes et redirections
- L'expansion des variables d'environnement
- Le développement de commandes intégrées
- La gestion de la mémoire et des erreurs

### 🧠 Compétences acquises

En complétant le projet Minishell, les étudiants développent des compétences essentielles en programmation C et programmation système :

- **Parsing des commandes** : Implémenter un lexer et un parser pour gérer la syntaxe du shell, les guillemets et les opérateurs.
- **Gestion des processus** : Utiliser fork, execve, waitpid pour l'exécution des commandes et le contrôle des processus.
- **Gestion des signaux** : Gérer les signaux comme SIGINT (Ctrl+C) et SIGQUIT (Ctrl+\) pour imiter le comportement de bash.
- **Implémentation des pipes** : Créer des pipelines entre commandes en utilisant pipe() et dup2().
- **Gestion des redirections** : Implémenter les redirections d'entrée/sortie (<, >, >>) et les here-documents (<<).
- **Variables d'environnement** : Étendre les variables ($VAR) et gérer l'environnement avec des builtins comme export/unset.
- **Commandes intégrées** : Développer des builtins du shell (echo, cd, pwd, exit, env, export, unset) sans fork.
- **Gestion d'erreurs** : Gestion robuste des erreurs avec des codes de sortie et messages appropriés.
- **Organisation du code** : Structurer le code en composants modulaires, en respectant les normes 42 pour le style et la documentation.

## Approche
Ce projet est assez vaste, avec de nombreux cas spécifiques à considérer. Le premier défi que j'ai rencontré était de me demander "*Par où commencer ?*"<br>

J'ai commencé Minishell deux semaines avant que **Poid-lourd** puisse me rejoindre. Pendant ce temps, j'ai travaillé sur les builtins et le parsing initial. Naturellement, j'ai dû créer une base d'exécution que **Poid-lourd** a complètement refaite à la fin de ses deux semaines. Avec le temps, nous avons rapidement défini qui devait faire quoi et comment le faire.<br>

- **Poid-lourd** : Exécution complète, redirections (<, <<, >>), et heredoc, que nous avons plus ou moins partagés pour la facilité.<br>

- **Moi** : Parsing complet, builtins, signaux.<br>

Nous avons géré la gestion d'erreurs et tout ce que je n'ai pas mentionné ensemble pour assurer une base solide et une logique cohérente. Nous avons rapidement réalisé que nos deux vrais défis seraient le parsing et l'exécution en raison des nombreux cas spécifiques dans BASH.<br>

Le projet est très gratifiant et nous a permis de développer des compétences cruciales en programmation et collaboration. Travailler en binôme sur un projet aussi complexe nous a appris à bien communiquer, à distribuer efficacement les tâches et à surmonter les obstacles ensemble.<br>

### **Fonctionnalités**

**Historique des commandes** : *Naviguer dans les commandes avec les flèches haut/bas.*<br>

**Pipes (|)** : *Chaîner les commandes pour passer la sortie d'une à l'autre.*<br>

**Redirections** : *Entrée (<), sortie (>), ajout (>>), et here-doc (<<).*<br>

**Gestion des guillemets** : *Guillemets doubles ("") et simples ('') échappent les caractères spéciaux.*<br>

**Variables d'environnement** : *Étendre les variables comme $VAR dans les commandes.*<br>

**Gestion des signaux** : *Gérer Ctrl+C, Ctrl+\, Ctrl+D comme dans bash.*<br>

**Built-ins** : *echo (-n), exit, env, export, unset, cd, pwd.*<br>

### **Fonctionnalités à ajouter :**

**Expansions avancées** : *Expansions de variables plus complexes et wildcards.*<br>

**Contrôle des jobs** : *Processus en arrière-plan et gestion des jobs.*<br>

**Mode script** : *Support pour l'exécution de scripts shell.*<br>

**Built-ins avancés** : *Plus de builtins similaires à bash et options.*<br>

### 📋 Table des matières

- [Caractéristiques](#caractéristiques)
- [Installation](#installation-1)
- [Utilisation](#utilisation)
- [Structure du projet](#structure-du-projet)
- [Compilation](#compilation-1)
- [Référence des fonctions](#référence-des-fonctions)
- [Crédits](#crédits-1)

<a name="caractéristiques"></a>

### ✨ Caractéristiques

- **Exécution de commandes** avec chemins absolus/relatifs et résolution PATH
- **Support des pipes** pour chaîner plusieurs commandes
- **Redirections** incluant entrée, sortie, ajout et here-documents
- **Gestion des guillemets** pour échapper les caractères spéciaux
- **Expansion des variables d'environnement** avec gestion correcte des guillemets
- **Gestion des signaux** imitant le comportement de bash (Ctrl+C, Ctrl+\, Ctrl+D)
- **Commandes intégrées** (echo, cd, pwd, exit, env, export, unset)
- **Historique des commandes** avec navigation par flèches
- **Conformité stricte C** avec les normes de l'école 42

<a name="installation-1"></a>

### 🚀 Installation

```bash
# Cloner le dépôt
git clone https://github.com/HaruSnak/42-minishell
cd 42-minishell
```

<a name="utilisation"></a>

### 💻 Utilisation

Compilez et lancez le shell :

```bash
make
./minishell
```

Exemples :
```bash
$ ls -la
$ echo "Hello World"
$ cat file.txt | grep "pattern" > output.txt
$ export VAR=value
$ $VAR
```

Contrôles :
- **Flèches haut/bas** : Naviguer dans l'historique des commandes
- **Ctrl+C** : Interrompre la commande actuelle
- **Ctrl+D** : Quitter le shell (EOF)
- **Ctrl+\** : Quitter avec dump core

<a name="structure-du-projet"></a>

### 📂 Structure du projet

```
42-minishell/
├── Makefile                    # Script de build
├── minishell.h                 # Fichier d'en-tête principal
├── minishell.c                 # Point d'entrée principal du shell
├── LICENSE                     # Fichier de licence
├── README.md                   # Ce fichier
├── README-Template.md          # Template pour README
├── includes/
│   ├── exec.h
│   ├── minishell.h
│   └── libft/                  # Bibliothèque personnalisée
├── readme/                     # Ressources README
└── srcs/                       # Fichiers sources
    ├── builtins/               # Commandes intégrées
    ├── errors/                 # Gestion d'erreurs
    ├── execution/              # Exécution des commandes
    ├── parsing/                # Parsing des commandes
    ├── redirections/           # Redirections I/O
    ├── signals/                # Gestion des signaux
    └── utils/                  # Fonctions utilitaires
```

<a name="compilation-1"></a>

### 🔧 Compilation

Compilez le projet en utilisant le Makefile :

```bash
make          # Compiler le shell
make clean    # Supprimer les fichiers objets
make fclean   # Supprimer l'exécutable et les fichiers objets
make re       # Recompiler tout
```

<a name="référence-des-fonctions"></a>

### 📚 Référence des fonctions

#### Fonctions principales
- [`main`](srcs/minishell.c) - Initialisation du shell et boucle principale
- [`parse_input`](srcs/parsing/) - Parsing et tokenisation des commandes
- [`execute_command`](srcs/execution/) - Logique d'exécution des commandes
- [`handle_signals`](srcs/signals/) - Configuration de la gestion des signaux

#### Fonctionnalités clés
- **Parsing** : Tokenise l'entrée, gère les guillemets et opérateurs
- **Exécution** : Fork les processus, gère les pipes et redirections
- **Builtins** : Implémente les commandes intégrées du shell
- **Environnement** : Gère les variables d'environnement et leur expansion

### 👨‍🎓 Note
<p align="left">
    <img width="201" height="169" alt="Image" src="https://github.com/user-attachments/assets/1e15fd1d-f7c7-4d97-b04a-468e342e1977" />
</p>

<a name="crédits-1"></a>

### 📖 Crédits

- **Norme 42** : [Standard C officiel](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf)
- **Manuel Bash GNU** : [Manuel de référence Bash](https://www.gnu.org/software/bash/manual/bash.html)
- **Bibliothèque Readline** : Pour l'édition de ligne de commande et l'historique

### 📄 Licence

Ce projet est sous licence **MIT** - voir le fichier [LICENSE](LICENSE) pour plus de détails.

</details>

---

[contributors-shield]: https://img.shields.io/github/contributors/HaruSnak/42-minishell.svg?style=for-the-badge
[contributors-url]: https://github.com/HaruSnak/42-minishell/graphs/contributors
[forks-shield]: https://img.shields.io/github/forks/HaruSnak/42-minishell.svg?style=for-the-badge
[forks-url]: https://github.com/HaruSnak/42-minishell/network/members
[stars-shield]: https://img.shields.io/github/stars/HaruSnak/42-minishell.svg?style=for-the-badge
[stars-url]: https://github.com/HaruSnak/42-minishell/stargazers
[issues-shield]: https://img.shields.io/github/issues/HaruSnak/42-minishell.svg?style=for-the-badge
[issues-url]: https://github.com/HaruSnak/42-minishell/issues
[linkedin-shield]: https://img.shields.io/badge/-LinkedIn-black.svg?style=for-the-badge&logo=linkedin&colorB=555
[linkedin-url]: https://www.linkedin.com/in/shany-moreno-5a863b2aa
[license-shield]: https://img.shields.io/github/license/HaruSnak/42-minishell.svg?style=for-the-badge
[license-url]: https://github.com/HaruSnak/42-minishell/blob/master/LICENSE
