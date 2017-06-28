---
lang      : fr
title     : ContrÃ´le de connaissances SE207 "SystemC"
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

*Ceci est un exemple de rÃ©ponse. **Merci d'effacer ce paragraphe** (mais de **laisser les groupes de trois tirets et les lignes vides avant et aprÃ¨s eux**) lorsque vous y Ã©crirez la vÃ´tre.*

- `X` ceci est X
- `Y` ceci est Y

```{.cpp}
// ceci est un exemple de code
int main() {
   return 0;
}
```
---

### Question 2

Pourquoi peut-on connecter *directement* la sortie (`sc_out<>`) d'un module Ã  la sortie d'un autre module mais pas Ã  une entrÃ©e (`sc_in<>`)?

---

---

### Question 3

- Que se passe-t-il si une boucle infinie existe dans une `SC_METHOD`?
- Que se passe-t-il si la fonction `wait()` est appelÃ©e dans cette boucle infinie?


---

---

### Question 4

Nous voulons modÃ©liser un bloc matÃ©riel synchrone (Ã  une horloge `clk`) dans lequel une Ã©tape de traitement doit attendre la fin d'une autre Ã©tape avant de commencer.

Pour ce fait, nous utilisons deux `SC_THREAD`, sensibles au front montant de l'horloge, pour modÃ©liser chaque Ã©tape.

Dans une premiÃ¨re implÃ©mentation, nous utilisons un `sc_mutex` pour synchroniser les de `SC_THREAD`.

```{.cpp}
    // Thread 1
    step1_end_mutex.lock();
    // Ã©tape 1 du traitement
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

---


### Question 5

- Pouvons-nous modÃ©liser au niveau RTL en utilisant un `SC_THREAD`?
- *Justifiez votre rÃ©ponse*


---

---
