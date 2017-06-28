---
lang      : fr
title     : Controle de connaissances SE207 "SystemC"
date      : 28 juin 2017
---

# Instructions

Ce contrÃ´le de connaissances est strictement individuel.
Vous devez modifier ce fichier pour y inclure vos rÃ©ponses puis l'ajouter Ã  votre dÃ©pÃ´t dans un dossier `CC` Ã  la racine de ce dernier.

Seules les parties entre *`---`* sont Ã  modifier.

# Questions

### Question 1

En SystemC, pour modÃ©liser des calculs sur des entiers signÃ©s, plusieurs types peuvent Ãªtre utilisÃ©s.
Donnez la liste de ces types (les grandes familles) en expliquant dans quels cas il est prÃ©fÃ©rable d'utiliser l'un plutÃ´t que l'autre.

---
Pour travailler sur un entier de XXbits, on peut utiliser des
- intXX_t
- sc_int<XX>
Les sc_int<XX> sont plus facilement utilisés lorsqu'il faut effectuer des calculs bit à bit dessus. Sinon, il est préférable d'utiliser des intXX_t.
---

### Question 2

Pourquoi peut-on connecter *directement* la sortie (`sc_out<>`) d'un module Ã  la sortie d'un autre module mais pas Ã  une entrÃ©e (`sc_in<>`)?

---
Pour connecter la sortie d'un module à l'entrée d'un autre, il faut utiliser un signal (par exemple) entre car il faut modéliser le caractère temporel des signaux électriques. Il n'y a cependant pas cette contrainte lorsque deux sorties sont liées.
---

### Question 3

- Que se passe-t-il si une boucle infinie existe dans une `SC_METHOD`?
- Que se passe-t-il si la fonction `wait()` est appelÃ©e dans cette boucle infinie?


---
- Etant donné qu'une SC_METHOD prend la main sur la simulation, une boucle infinie à l'intérieur d'une SC_METHOD bloquerait la simulation. Il faut utiliser un SC_THREAD par exemple pour solutionner ce problème.
- Si la fonction wait est appelée, la simulation pourra reprendre mais elle sera à nouveau bloquée à la reprise de la SC_METHOD.
---

### Question 4

Nous voulons modÃ©liser un bloc matÃ©riel synchrone (Ã  une horloge `clk`) dans lequel une Ã©tape de traitement doit attendre la fin d'une autre Ã©tape avant de commencer.

Pour ce fait, nous utilisons deux `SC_THREAD`, sensibles au front montant de l'horloge, pour modÃ©liser chaque Ã©tape.

Dans une premiÃ¨re implÃ©mentation, nous utilisons un `sc_mutex` pour synchroniser les de `SC_THREAD`.

```{.cpp}
    // Thread 1
    step1_end_mutex.lock();
    â€¦
    step1_end_mutex.unlock();
    wait();


    // Thread 2
    wait();
    // attente de la fin de l'Ã©tape 1
    step1_end_mutex.lock();
    // passage Ã  l'Ã©tape suivante
    â€¦
```

Dans une seconde implÃ©mentation nous utilisons un `sc_signal` dont nous examinons la valeur Ã  chaque front de l'horloge.

```{.cpp}
    // Thread 1
    // Ã©tape 1 du traitement
    end_step1 = false;
    â€¦
    end_step1 = true;
    wait();

    // Thread 2
    wait();
    // attente de la fin de l'Ã©tape 1
    while(!end_step1) wait();
    // passage Ã  l'Ã©tape suivante
    â€¦
```

- Expliquez briÃ¨vement le fonctionnement.
- En justifiant votre rÃ©ponse:
    * Voyez-vous des diffÃ©rences en termes de ressources utilisÃ©es pour la simulation (temps de calcul, mÃ©moireâ€¦)?
    * Voyez-vous des diffÃ©rences quant Ã  la prÃ©cision temporelle des deux implÃ©mentations?

---
- Dans le premier cas, un même mutex est lock par les deux thread (d'abord la thread 1, puis le n 2). Lorsque le thread 1 relache enfin le mutex, on sait où se trouve les deux thread, la synchronisation est faite !
- Dans la seconde implementation, le thread 2 utilise un signal partagé par les deux thread pour se tenir informé de l'état de l'autre thread.
- Les mutex utilisent des zones mémoire spécifiques qui sont limités. La deuxième version est appelé à chaque coup d'horloge alors que la 1ere se met en pause jusqu'au 'réveil'.
- La première version est asynchrone, contrairement à l'autre, ce qui est une différence majeure.
---


### Question 5

- Pouvons-nous modÃ©liser au niveau RTL en utilisant un `SC_THREAD`?
- *Justifiez votre rÃ©ponse*


---
On peut se servir d'un SC_THREAD pour modéliser du RTL mais il faut bien noter que l'implémentation RTL n'aura rien a voir avec des thread niveau logiciel. 
---
