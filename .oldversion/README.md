# Minishell## Plan d’attaque détaillé (y compris bonus)

### Étape 1 — Initialisation du projet (1 jour)
- Copier libft si nécessaire : Fait
- Écrire un Makefile basique : Fait
- Créer l’architecture : Fait

### Étape 2 — Lecture de la ligne & historique (1–2 jours)
- Intégrer `readline()` et `add_history()` : Fait 
- Afficher un prompt personnalisé : Fait 

### Étape 3 — Tokenisation (2–3 jours)
- Se renseigner sur lexer de bash 
- Séparer la ligne en tokens : mots, quotes, redirections, pipes  
- Gérer :  
- quotes simples (`'…'`) sans expansion  
- quotes doubles (`"…"`) avec expansion `$`  

### Étape 4 — Parser & AST (3–4 jours)
- Construire une structure interne (liste chaînée ou AST)  
- Représenter :  
- commandes séquentielles  
- pipelines  
- Stocker redirections et arguments  

### Étape 5 — Exécution simple (2–3 jours)
- Utiliser `fork()`, `execve()`, `waitpid()`  
- Recherche d’exécutables dans `$PATH` et chemins relatifs/absolus  

### Étape 6 — Built-ins internes (2–3 jours)
- Implémenter : `echo [-n]`, `cd [path]`, `pwd`, `export`, `unset`, `env`, `exit`  
- Exécuter certains built-ins sans `fork()` (ex. `cd`, `exit`)  

### Étape 7 — Redirections & heredoc (3 jours)
- `<`, `>`, `>>` via `dup2()`  
- `<<` (heredoc) : lire jusqu’au délimiteur dans un tmpfile, sans historique  

### Étape 8 — Pipes multiprocessus (2–3 jours)
- Chaîner plusieurs `pipe()` + `fork()`  
- Gérer correctement les fermetures de descripteurs  

### Étape 9 — Expansion des variables (2 jours)
- `$VAR`, `$?` pré-expansion avant exécution  
- Assurer absence de fuites mémoire  

### Étape 10 — Gestion des signaux (2 jours)
- `sigaction()` pour `SIGINT` (Ctrl-C) et `SIGQUIT` (Ctrl-\)  
- Variable globale pour le dernier signal reçu  
- Quitter au Ctrl-D et rafraîchir le prompt au Ctrl-C  

### Étape 11 — Nettoyage & tests unitaires (2–3 jours)
- Vérifier fuites mémoire avec Valgrind  
- Valider la Norme (norminette) et les flags `-Wall -Wextra -Werror`  
- Couvrir les cas d’erreur (`perror`, `strerror`)  

### Étape 12 — Implémentation des bonus (4–5 jours)
- Opérateurs logiques `&&` et `||` : étendre le parser, gérer priorité et parenthèses  
- Wildcards `*` : lister `opendir()`/`readdir()` et matcher  

### Étape 13 — Phase finale & relecture (2 jours)
- Peer-review croisée entre mates  
- Ajustements et correction du README  
- Simulation de défense  

## Conseils pratiques

- **Itération rapide** : validez chaque module avec des tests minimalistes  
- **Gestion de version** : commits fréquents, branches thématiques (`parser`, `executor`, `bonus`)  
- **Norme & Makefile** : vérifiez la compilation avant chaque fin de journée  
- **Communication** : répartissez les tâches, pair programming pour les parties complexes  
- **Tests** : scripts bash + cas bord, hors dépôt évalué (mais disponibles pour la défense)  
