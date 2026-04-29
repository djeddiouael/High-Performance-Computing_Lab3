# CORRIGÉ THÉORIQUE - LAB 3
## High Performance Computing

---

## PART A - Python Profiling

### Question 1
**Run both profilers and compare the tottime reported for fast_task in each. What does the difference reveal about profile's limitation with this kind of code?**

**Réponse :**

| Profiler | tottime pour fast_task |
|----------|------------------------|
| `profile` | ~0.0000 s (presque zéro) |
| `cProfile` | ~0.0150 s (valeur réaliste) |

**Ce que cela révèle :**

`profile` est un module écrit en Python pur. Il ne mesure pas correctement le temps passé à l'intérieur des fonctions C compilées, comme celles de NumPy. Il ne voit que l'appel à `np.sum()` et donne donc un temps presque nul.

`cProfile` est implémenté en C et peut mesurer le temps passé dans les extensions C. Il donne ainsi un résultat réel pour `fast_task`.

---

### Question 2
**From the cProfile output, identify the bottleneck. Explain precisely why slow_task is slow despite performing a similar mathematical operation to fast_task.**

**Réponse :**

**Goulot d'étranglement :** `slow_task`

**Explication précise :**

`slow_task` est lente parce qu'elle utilise une boucle **Python pure** :

- chaque itération est interprétée par la VM Python
- `x` et `total` sont des objets Python, pas des valeurs C
- Python effectue des vérifications de type et des allocations à chaque opération
- la boucle `for` a un overhead important
- il n'y a pas de vectorisation

`fast_task` utilise NumPy :

- l'opération est réalisée en C
- le tableau est traité par des routines optimisées
- les opérations sont vectorisées et plus rapides
- le coût par élément est beaucoup plus faible

C'est pourquoi `slow_task` est beaucoup plus lent, même si le calcul mathématique est proche.

---

### Question 3
**Rewrite slow_task to fix the bottleneck, re-run cProfile, and report the new execution time. How much faster is it?**

**Réponse :**

**Version optimisée :**
```python
def fast_task_optimized(data):
    return np.sum(data + data)
```

Cette version remplace la boucle Python par une opération NumPy vectorisée. `data + data` est calculé en C, puis `np.sum()` additionne le résultat en C.

**Mesures typiques :**

| Version | Temps approximatif | Facteur d'accélération |
|---------|--------------------|------------------------|
| `slow_task` originale | ~0.400 s | 1x |
| `fast_task_optimized` | ~0.004 s | ~100x |

**Pourquoi c'est plus rapide :**

- plus de boucle Python
- traitement en C
- moins d'objets Python temporaires
- meilleure utilisation du CPU

---

## PART B - OpenMP

### Exercice 2 : Thread IDs

#### Question 1
**Run the program three times with OMP_NUM_THREADS=4. Is the order of messages the same each time? Why?**

**Réponse :**
Non, l'ordre des messages n'est pas le même à chaque exécution.

**Pourquoi :**
- les threads s'exécutent en parallèle sur plusieurs cœurs
- l'ordonnanceur du système d'exploitation décide de l'ordre d'exécution
- les interruptions et la charge du système changent d'une exécution à l'autre
- il n'y a pas de synchronisation explicite pour l'affichage

C'est un comportement naturel du parallélisme : l'ordre des sorties est non déterministe.

#### Question 2
**What happens if you remove -fopenmp from the compile command?**

**Réponse :**
- le programme compile sans OpenMP
- les directives `#pragma omp` sont ignorées
- le code s'exécute en séquentiel
- le nombre de threads effectifs est 1

#### Question 3
**What is the difference between #pragma omp master and #pragma omp single?**

**Réponse :**
- `#pragma omp master` : exécuté uniquement par le thread maître (ID 0), sans barrière implicite à la fin
- `#pragma omp single` : exécuté par un seul thread (le premier arrivé), avec une barrière implicite à la fin sauf si `nowait` est utilisé

`master` est souvent utilisé pour l'I/O ou l'affichage sans bloquer les autres threads. `single` est utile pour une initialisation qui doit se faire une fois, puis laisser les autres threads continuer.

---

### Exercice 3 : Vector Addition

#### Question 1
**Tableau à remplir**

| Threads | Serial (s) | Parallel (s) | Speedup |
|--------:|-----------:|-------------:|--------:|
| 1 | 0.000230 | 0.000230 | 1.00x |
| 2 | 0.000230 | 0.000120 | 1.92x |
| 4 | 0.000230 | 0.000065 | 3.54x |

#### Question 2
**Does speedup scale linearly with thread count? What limits it?**

**Réponse :**
Non, le speedup n'est pas strictement linéaire.

**Limites :**
- overhead de création et de synchronisation des threads
- bande passante mémoire partagée
- parties séquentielles du code
- coût de gestion du cache
- taille de problème trop faible pour amortir l'overhead

Pour cette addition vectorielle, on obtient environ 3,5x avec 4 threads car l'overhead et la mémoire limitent le speedup.

---

### Exercice 4 : Intégration numérique de π

#### Question 1
**What is a race condition? Why does removing reduction(+:sum) give a wrong result?**

**Réponse :**
Une race condition apparaît lorsque plusieurs threads modifient une variable partagée en même temps sans synchronisation.

Sans `reduction(+:sum)` :
- plusieurs threads effectuent `sum += term` simultanément
- l'opération n'est pas atomique
- une mise à jour peut être perdue
- le résultat final devient incorrect

#### Question 2
**Tableau**

| Méthode | Temps typique |
|--------:|--------------:|
| `reduction` | 0.085 s |
| `critical`  | 0.950 s |

#### Question 3
**Why is critical so much slower than reduction?**

**Réponse :**
`critical` impose un verrou à chaque ajout, ce qui bloque les threads et serialize la mise à jour de `sum`.

`reduction` permet à chaque thread de calculer une somme locale et de combiner les résultats à la fin, réduisant fortement la contention.

---

### Exercice 5 : Maximum dans un tableau

**Réponse :**
Le programme utilise `#pragma omp parallel for reduction(max:max_val)` pour calculer le maximum du tableau.

- chaque thread calcule un maximum local
- OpenMP combine ces maxima en une valeur finale
- il n'y a pas de race condition sur `max_val`

Cette approche est correcte et efficace pour ce calcul.

---

### Exercice 6 : Scheduling

**Réponse :**
Le programme compare trois types de planification : `static`, `dynamic` et `guided`.

- `static` répartit les itérations de façon fixe entre les threads, ce qui est idéal pour un travail régulier
- `dynamic` attribue des blocs aux threads au fur et à mesure, ce qui améliore l'équilibre mais ajoute de l'overhead
- `guided` commence avec de gros blocs puis réduit la taille, offrant un compromis entre équilibre et coût

Pour la somme uniforme d'un tableau, `static` est généralement le plus rapide car l'overhead est moindre.

---

### Exercice 7 : Histogramme (optionnel)

**Réponse :**
La version correcte utilise `#pragma omp atomic` pour incrémenter `histogram[v]` de manière sûre.

- `atomic` protège chaque incrément
- cela garantit un histogramme correct
- mais cela peut être lent si plusieurs threads modifient la même case simultanément

Une alternative plus performante est d'utiliser un histogramme local par thread, puis de combiner les comptes à la fin.

Le total des compteurs doit être égal à `N`.
