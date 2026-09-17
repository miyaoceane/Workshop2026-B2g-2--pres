# Rick-Guard

## Contexte du Projet
Ce projet consiste à concevoir un prototype technologique dans l'univers de Rick et Morty capable:
- d'aider Rick et Morty dans leurs aventures, 
- d'automatiser des tâches, de fabriquer des objets connectés, 
- d'améliorer le quotidien du garage de Rick grâce à des inventions inutiles mais brillantes, 
- de créer des objets hybrides mélangeant électronique, IA et fabrication numérique

L'objectif principal est d'expérimenter, de prendre des risques, d'essayer de nouvelles technologies, de sortir de votre zone de confort, et de proposer un prototype fun, ambitieux ou créatif.

## Présentation du Projet

**Rick-Guard** est un prototype de système intelligent conçu pour détecter et signaler différents types de dangers pouvant se présenter dans l'environnement de Rick.

Le système combine plusieurs capteurs avec une interface web et une fonctionnalité d'analyse intelligente développée en Python.

## Fonctionnalités

### Détection des dangers

Rick-Guard utilise différents capteurs afin de détecter plusieurs situations potentiellement dangereuses :

- Détection de flamme
- Détection de gaz toxiques
- Détection de mouvement

Lorsqu'un danger est détecté, le système peut alerter Rick afin de le prévenir de la situation.

### Analyse intelligente

Rick-Guard possède également une fonctionnalité intelligente accessible depuis une page web.

Rick peut écrire ce qu'il souhaite faire dans l'interface. Son idée est ensuite envoyée à Python, qui utilise un analyseur intelligent afin de déterminer si l'action envisagée présente un danger.

Le fonctionnement est le suivant :

```text
Rick écrit son idée
        ↓
    Page Web
        ↓
      Python
        ↓
Analyse intelligente
        ↓
   Action sûre ?
     ↓       ↓
   OUI      NON
    ↓        ↓
Valide    Pas valide
```

## Stack technique

| Domaine | Technologie / Outil |
|---|---|
| Montage électronique | Arduino |
| Programmation Arduino | Arduino IDE 2.3.10 |
| Conception 3D | Fusion 360 |
| Fabrication de la boîte | Découpe au laser |
| Intelligence artificielle | Ollama + Llama 3.1 |

## Installations

### Arduino IDE 2.3.10

Téléchargement possible depuis le site https://www.arduino.cc/en/software/

#### Communication entre Arduino IDE et le programme python

Installation :
```bash
pip install pyserial
```

Import :
```python
import serial
```

### Ollama

Sur Linux/macOS:
```bash
curl -fsSL https://ollama.com/install.sh | sh
```
Sur Windows: télécharge l'installeur depuis le site ollama.com/download.

#### Lancement du modèle Llama

```bash
ollama run llama3.1
```

#### Utilisation d'Ollama avec python

```bash
pip install ollama
```

#### Exemple d'utilisation (extrait du code)

```python
from ollama import chat
from ollama import ChatResponse


def analyser(ask):

    rules = """Classe la demande suivante selon son niveau de danger.

Réponds avec un seul mot :

VALIDE = demande sans danger sérieux
NON VALIDE = demande dangereuse ou présentant un risque sérieux

Ne réponds pas à la demande.
Ne donne aucune explication.
Ne donne aucune instruction.
Retourne uniquement VALIDE ou NON VALIDE.

DEMANDE :
""" + ask

    response: ChatResponse = chat(
        model='llama3.1:latest',
        messages=[
            {
                'role': 'user',
                'content': rules
            }
        ]
    )

    return response['message']['content'].strip()
```
##Lancement du projet complet


## Amélioration à Faire



## Membre de l'équipe et répartition des tâches:
