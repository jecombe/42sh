| <h1>42SH</h1> |
| :-----------:|
| <h2>Description</h2> |
| path to data files to supply the data that will be passed into templates. |
| engine to be used for processing templates. Handlebars is the default. |
| extension to be used for dest files. |

| <h2>Partie Obligatoire</h2> | <h2>status</h2> |
| :-----------: | :-----------:|
| Affichage d’un prompt. | √ |
| lecture de la ligne de commande, sans édition de ligne. | √ |
| Exécution de commandes simples avec leurs paramètres et gestion du PATH. | √ |
| Les opérateurs de redirection suivants : ">", ">>", "<". | √ |
| Les opérateurs logiques "&&" et "\|\|". | √ |
| Le séparateur ";" | √ |
| Builtins : echo | √ |
| Gestion correcte des espaces et des tabulations. | X |
| Gestion des erreurs et de la valeur de retour des commandes | X |
| cd | X |
| exit | X |
| env | X |
| setenv | X |
| unsetenv | X |
| Les pipes "\|" | X |
| Les aggrégations de descripteurs de fichiers, par exemple pour fermer la sortie d’erreur | X |

| <h2>Bonus Finis</h2> |
| :-----------:|
| Les inhibiteurs """ (double quote), "’" (simple quote) et "\" (backslash). |
| Les redirections avancées : l’aggrégation des sorties de fichier et le heredoc "<<". |
| Edition de ligne telle que demandée dans le ftsh3. |

| <h2>Bonus en cours</h2> |
| :-----------:|
| les variables locales et les builtin unset et export. |
| L’historique des commandes et les builtins history et "!" avec toutes leurs options
si elles en ont. |
| Complétion dynamique. |
| Le Job control et les builtins jobs, fg et bg, et l’operateur "&". |
| Les back quotes "‘". |
| Rechercher dans l’historique avec ctrl+R |
| La complétion simple ou avancée avec tab. |
