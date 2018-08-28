| <h1 background-color: black>42SH</h1> |
| :-----------:|
| <h2>Description</h2> |
| Ce projet consiste à créer de toutes pièces un shell complet, en reprenant le travail effectué sur votre 21sh. Un jeu minimum de fonctionnalités vous sont demandées, à partir duquel vous allez constuire votre propre shell abouti - en allant potentiellement jusqu'au job control et au shell script. Ce projet vous permet donc de voir ou revoir une très large palette des fonctionnalités UNIX (et POSIX) standard. |

| <h2>Partie Obligatoire</h2> | <h2>status</h2> |
| :-----------: | :-----------:|
| NORME. | 🐌 |
| LEAKS. | 🐌 |
| Affichage d’un prompt. | ✅ |
| lecture de la ligne de commande, sans édition de ligne. | ✅ |
| Exécution de commandes simples avec leurs paramètres et gestion du PATH. | ✅ |
| Les opérateurs de redirection suivants : ">", ">>", "<". | ✅ |
| Les opérateurs logiques "&&" et "\|\|". | ✅ |
| Le séparateur ";" | ✅ |
| Gestion correcte des espaces et des tabulations. | ✅ |
| Gestion des erreurs et de la valeur de retour des commandes | ✅ |
| echo | ✅ |
| cd | ❌ |
| exit | ❌ |
| env | ❌ |
| setenv | ❌ |
| unsetenv | ❌ |
| Les pipes "\|" | ✅ |
| Les aggrégations de descripteurs de fichiers, par exemple pour fermer la sortie d’erreur | 🐢 |

| <h2>Partie Bonus</h2> | <h2>status</h2> |
| :-----------: | :-----------:|
| Les inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash). | ✅ |
| Les redirections avancées : l’aggrégation des sorties de fichier et le heredoc "<<". | ✅ |
| Edition de ligne telle que demandée dans le ftsh3. | ✅ |
| les variables locales et les builtin unset et export. | 🐇 |
| L’historique des commandes et les builtins history et "!" avec toutes leurs options si elles en ont. | ❌ |
| Complétion dynamique. | 🐢 |
| Le Job control et les builtins jobs, fg et bg, et l’operateur "&". | 🐌 |
| Les back quotes "‘". | ✅ |
| Rechercher dans l’historique avec ctrl+R. | ❌ |
| La complétion simple ou avancée avec tab. | 🐢 |

PROBLEMES A RESOUDRE:
\_TABLE DE HASH
\_\> l
\_\`\` > 2

SEGFAULT A RESOUDRE:
\_ENVIRONNEMENT VIDE
