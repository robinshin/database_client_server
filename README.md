# Base de données client-serveur en C++ et en Javaswing

# Première partie : C++
Le but de ces travaux pratiques est de créer l'ébauche du logiciel d'une set-top box multimédia permettant de jouer de la musique, des vidéos, des films, d'afficher des photos, etc. Ce logiciel sera realisé par étapes, en se limitant à la déclaration et l'implémentation de quelques classes et fonctionnalités typiques que l'on complétera progressivement. Noter qu'il est utile de lire le texte de chaque étape en entier avant de la traiter (en particulier les notes ou remarques qui donnent des indications).
Comme il faudra rendre le TP et un README décrivant brièvement votre travail pensez à noter au fur et à mesure ce que vous avez fait et les réponses aux questions. Lorsqu'il y a des des modifications importantes du code source (en particulier dans la fonction main()) il est utile de conserver la version antérieure en commentaires ou, mieux, entre #ifdef VERSION_TRUC et #endif, comme expliqué plus bas.

##1e Etape: Démarrage
1. Ouvrir une fenêtre Terminal
2. Créer un répertoire pour les fichiers de ce TP, par exemple : mkdir inf224
3. Aller dans ce répertoire : cd inf224
4. Copier le fichier Makefile dans ce répertoire. Du fait de la présence de tabulations, ne pas faire de coupé collé, utiliser la commande du navigateur Web pour enregister le fichier. Si le navigateur rajoute l'extension .txt au Makefile il faut l'enlever.
5. Lancer un IDE approprié pour le développement C/C++ (pas un simple éditeur de texte comme gedit, etc.). Vous pouvez par exemple utiliser QtCreator qui est accessible depuis le menu Programmation ou depuis le Terminal en tapant la commande qtcreator &.
6. ATTENTION : votre programme doit pouvoir être compilé et exécuté juste en tapant la commande make run dans le Terminal depuis une machine Unix de l'Ecole. Si vous utilisez un autre IDE que QtCreator (Emacs, Eclipse, etc.) il doit utiliser ce Makefile pour compiler le projet. Un programme qui ne compile pas en tapant make sera considéré non rendu !
Pour créer un projet compatible avec un Makefile avec QtCreator :
* Fichier puis Nouveau fichier ou projet...
* Importer un projet puis Importer un projet existant
* indiquer un nom de projet et choisir le répertoire que vous avez précédemment créé, puis valider autant de fois que nécessaire.
Ceci crée un fichier qui a le nom du projet avec l'extension .creator. Ce fichier permettra de réouvrir votre projet lors d'une session ultérieure, en sélectionnant Fichier puis Ouvrir un fichier ou projet... dans QtCreator (ou en double cliquant sur ce fichier si l'environnement est bien configuré).


##2e Etape: Classe de base
Ecrire la déclaration (fichier header .h) et l'implémentation (fichier source .cpp) de la classe de base de l'arbre d'héritage des classes d'objets multimédia. Cette classe de base contiendra ce qui est commun à tous les objets multimédia. On s'en servira ensuite pour définir des sous-classes spécifiques à chaque type de donnée (par exemple une classe photo, vidéo, film, morceau de musique, etc.)
Pour créer ces deux fichiers, dans QtCreator cliquer : Fichier puis Nouveau fichier ou projet... puis Classe C++ (le nom du .h et du .cpp sera forgé à partir de celui de la classe). Noter aussi que, par convention, les noms de vos classes devront commencer par une majuscule et ceux des variables et des fonctions par une minuscule.
Pour simplifier, cette classe de base n'aura que deux variables d'instance:
* Le nom de l'objet multimédia qui devra être de type string (ne pas utiliser les horribles char* du langage C !)
* Le nom du fichier associé à l'objet multimédia. Il s'agit du chemin complet (pathname) permettant d'accéder à ce fichier (une photo jpeg, une vidéo mpeg, etc.) dans le système de fichiers Unix.
Déclarer et implémenter deux constructeurs (un sans argument, un avec arguments), le destructeur, ainsi que les accesseurs ("getters") et modifieurs ("setters") pour pouvoir lire ou modifier les variables d'instance.
Déclarer et implémenter une méthode d'affichage permettant d'afficher la valeur des variables de l'objet. Cette méthode, qui s'inspirera de l'exemple vu en cours, ne modifiera pas l'objet et affichera les données sur un ostream, c'est-à-dire un flux générique de sortie. Ceci vous permettra d'utiliser la même fonction pour afficher sur le Terminal, un fichier ou un buffer de texte, ce qui sera utile plus tard. Concrètement:
* votre fonction doit avoir un paramètre de type ostream&. N'oubliez pas le & on verra à quoi il sert ultérieurement.
* pour afficher sur le Terminal, il suffira que cette fonction ait pour argument cout, c'est-à-dire la sortie standard (c'est l'abréviation de "console out").
* noter que votre méthode d'affichage ne doit en aucun cas créer ou renvoyer une string comme le ferait toString() en Java. Les buffers de texte (stringstream), que l'on utilisera dans une autre question font cela automatiquement.

Par ailleurs pensez à :
* inclure dans votre header les déclarations des objets de la bibliothèque standard dont vous avez besoin, c'est-à-dire au moins string et iostream. N'oubliez pas non plus qu'ils sont définis dans le namespace std.
* utiliser le mot-clé const pour les fonctions et les paramètres des fonctions là ou c'est souhaitable (on rappelle que toutes les fonctions qui ne modifient pas les variables d'instances doivent être const).

Pour compiler le fichier et corriger les erreurs
* Si vous utilisez QtCreator, vous devrez peut-être cliquer sur Liste des Projets dans la barre du haut puis selectionner Fichiers Système pour faire apparaître les fichiers du répertoire de travail (en particulier le fichier Makefile)
* Ouvrez le fichier Makefile en double-cliquant dessus dans la liste des fichiers pour modifiez EXEC, le nom du programme que l'on veut produire et SOURCES, la liste de vos fichiers .cpp (séparés par des blancs). Ne mettez pas les .h dans SOURCES.
* Cliquer sur le marteau de QtCreator (en bas à gauche) ou tapez Control-B. Une barre horizontale indique l'état de la compilation : tant qu'elle est verte tout va bien, si elle devient rouge il y a une erreur ! Dans ce cas, cliquer sur la barre pour afficher la liste des erreurs. Il suffit de cliquer sur une erreur pour faitre apparaître le code source qui a provoqué l'erreur.
* Si vous obtenez l'erreur "make: *** No rule to make target `main.o', needed by `myprog'. Stop." c'est normal, c'est juste que vous n'avez pas encore créé le fichier main.cpp.


##3e Etape: Programme de test
Un programme exécutable nécessite la présence d'une fonction main(). Cette fonction ne doit pas se trouver dans l'implémentation d'une classe car ceci interdirait sa réutilisation ultérieure. On va donc créer un autre fichier, appelé par exemple main.cpp qui va implémenter la fonction main().
Pour tester, créer quelques instances de la classe de base (en utilisant new) dans main() et vérifier que la fonction d'affichage affiche correctement la valeur des attributs dans le Terminal. Noter que votre code doit (et devra toujours par la suite) respecter le principe d'encapsulation : on ne doit donc jamais accéder aux attributs des objets autrement que par des méthodes.
Pour compiler et générer l'exécutable : pensez à rajouter main.cpp dans SOURCES dans le Makefile puis faites comme précédemment.
Pour exécuter le programme : plusieurs solutions:
* depuis QtCreator en cliquant la flèche verte à gauche et en sélectionnant l'exécutable
* en tapant make run dans le Terminal (remarque: make ou make all compile seulement, tandis que make run compile et exécute)
* en tapant le nom du programme précédé de ./ (par exemple : ./myprog) dans le Terminal.

Pensez à :
* Indenter votre code source et le rendre aussi lisible que possible : en séparant les méthodes par des lignes blanches, en mettant des espaces autour des = et après les , et les ; en passant à la ligne pour que votre code ne dépasse pas environ 80 caractères (on peut passer à la ligne autant de fois que l'on veut, ca n'a aucun impact sur la compilation mais ca rend le code beaucoup plus lisible et ca évite pas mal d'erreurs).
* Notez qu'avec la plupart des IDEs Control-I indente automatiquement la ligne courante et que Control-A Control-I indente tout le texte.
* Commenter votre code source et en particulier les headers afin de pouvoir générer automatiquement la documentation grâce à Doxygen. On pourra pour l'instant se limiter aux fonctionnalités de base de Doxygen vues en cours, ne commenter que l'essentiel, et compléter ultérieurement.


##4e Etape: Photos et videos
On va maintenant créer deux sous-classes de la classe de base, l'une correspondant à une photo, l'autre à une vidéo. Ces classes pourraient bien sûr comprendre de nombreux attributs mais on va faire simple pour ne pas perdre de temps :
* une vidéo a une durée, c'est-à-dire une valeur numérique intégrale,
* une photo peut être caractérisée par un latitude et une longitude, c'est-à-dire deux valeurs numériques réelles.
Ces deux classes devront être déclarées (et implémentées) dans des fichiers qui leurs sont propres pour obtenir une plus grande modularité et faciliter la réutilisation. Ces classes étant simples, on pourra les implémenter dans les headers si on le souhaite (auquel cas il ne doit pas y avoir de fichier .cpp).
Déclarer et implémenter les constructeurs, les accesseurs, les modifieurs et la méthode d'affichage (qui doit avoir la même signature que dans la classe parente, const compris s'il y en a un). Pour simplifier le code, on pourra éventuellement ne définir qu'un seul constructeur par classe grâce aux paramètres par défaut. N'oubliez pas d'initialiser les variables qui ont des types de base dans les constructeurs sinon leur valeur sera aléatoire (contrairement aux objets, qui sont initialisés automatiquement grâce à leurs constructeurs).
Enfin, déclarer et implémenter une méthode qui permette de jouer l'objet multimédia, c'est-à-dire, suivant le cas, d'afficher la photo ou de jouer la vidéo. Concrètement, cette fonction appellera un programme Unix (par exemple "mpv" pour une vidéo ou "imagej" pour une photo) via la fonction standard system(), exemple:
system("mpv nom_du_fichier &");    // nom_du_fichier est le chemin complet

Pour créer l'argument de system() il suffit de concaténer les strings avec l'opérateur +, puis d'appeler la méthode c_str() de la string résultante pour la convertir en char * (car system() prend une char * en argument). N'oubliez pas le & afin de lancer le programme Unix en tâche de fond.

Comme pour la fonction d'affichage, la fonction pour jouer l'objet ne modifie pas l'objet et elle doit être déclarée dans les classes Photo et Video et dans la classe de base afin de permettre un appel polymorphique sur la hiérarchie de classes. Cependant, contrairement à la fonction d'affichage, elle ne peut pas avoir d'implementation au niveau de la classe de base (car a priori chaque type d'objet nécessite un utilitaire différent pour être joué). Comment appelle-t'on ce type de méthode et comment faut-il les déclarer ?
Modifier le Makefile si nécessaire (on rappelle qu'il ne faut pas mettre les .h dans SOURCES). Compiler, corriger les éventuelles erreurs et tester le programme. Si vous avez fait correctement ce qui précède, il ne sera plus possible d'instancer des objets de la classe de base. Pourquoi ?


##5e Etape: Traitement générique (en utilisant le polymorphisme)
On veut maintenant pouvoir traiter génériquement une liste comprenant à la fois des photos et des vidéos. Pour ce faire créer dans main.cpp un tableau dont les éléments sont tantôt une photo tantôt une vidéo. Ecrire ensuite une boucle permettant d'afficher les attributs de tous les élements du tableau (ou de les "jouer"). Cette boucle n'a pas besoin de connaître le type des élements : elle doit pouvoir traiter de la même manière tous les objets dérivant de la classe de base.
Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ? Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ? Quel est le type des éléments du tableau : est-ce que ce tableau contient les objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.
Compiler, exécuter, et vérifier que le résultat est correct.


##6e étape. Films et tableaux
On veut maintenant définir une sous-classe Film dérivant de la classe Video. Une particularité des films est qu'ils sont composés de plusieurs chapitres ce qui permet d'accéder rapidement à une partie du film. Pour ce faire on va utiliser un tableau d'entiers contenant la durée de chaque chapitre. Il serait en fait préférable d'utiliser un vecteur de la librairie C++ mais on va ne pas le faire dans cette question pour illustrer certaines difficultés que peuvent poser les pointeurs et tableaux en C et C++.
Ecrire la classe Film, qui doit avoir :
* le ou les constructeurs adéquats.
* un modifieur permettant de passer en argument un tableau de durées
* un (ou des) accesseur(s) retournant le tableau de durées et le nombre de chapitres
* une méthode d'affichage affichant la durée des chapitres (la méthode pour jouer l'objet n'a pas besoin d'être redéfinie)
Attention :
* En C/C++, quand on passe un tableau en argument à une fonction c'est seulement l'ADRESSE du premier élement qui est recopiée (le paramètre correspondant de la fonction est toujours un pointeur, même lorsque la syntaxe suggère autre chose). La fonction n'a donc AUCUN MOYEN de savoir le nombre d'éléments du tableau ! Il faut donc obligatoirement également le passer en argument (ou utiliser une convention, par exemple les char * du C se terminent toujours par un 0).
* Cette opération ne copie donc pas le contenu du tableau ce qui signifie qu'il est partagé par la fonction et par l'appelant (noter que c'est pareil en Java).
* Ceci ne pose pas problème pour un appel de fonction mais rompt l'encapsulation si ce tableau est utilisé tel quel comme variable d'instance. En effet, l'objet contiendrait alors un tableau qui pourrait être modifié et même détruit par l'appelant ! Le même problème se poserait en Java sauf que le tableau ne pourrait pas être détruit.
Que faut-il faire pour que l'objet Film ait plein contrôle sur ses données et que son tableau de durées des chapitres ne puisse pas être modifié (ou pire, détruit) à son insu ? (c'est l'objet qui doit pouvoir modifier ce qui lui appartient, pas les autres !)
Attention, le même problème se pose si un accesseur retourne directement ce tableau sans prendre les précautions nécessaires : la encore le contenu du tableau n'est pas récopié et l'appelant peut le modifier à sa guise. Quelle est la solution très simple que propose C/C++ pour éviter ce problème ?
Plus généralement, ces problèmes se posent chaque fois qu'une des variable d'instance d'un objet pointe sur un objet ou un tableau. La question est alors de savoir qui a la responsabilité du pointé.
Implementez votre classe et vérifiez que le resultat est correct en modifiant et/ou détruisant le tableau qui lui est passé en argument puis en appelant la fonction d'affichage de l'objet (NB: il faut répéter l'opération pour vérifier que c'est correct car les erreurs de mémoire sont en partie aléatoires).


##7e étape. Destruction et copie des objets
Contrairement à Java ou C#, C/C++ ne gère pas la mémoire dynamique automatiquement (*) : comme il n'y a pas de ramasse miettes, tout ce qui a été créé avec new doit être détruit avec delete sinon on aura des fuites mémoires. Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit leurs instances ?
De même, la copie d'objets peut poser problème dans certains cas. Pourquoi et que faudrait-il faire ?
Modifiez le code de manière à éviter les fuites mémoire. Si vous n'avez pas pris de retard, modifiez également le code pour gérer la copie correctement (sinon dites juste ce qu'il faudrait faire). Faites quelques tests dans main() pour vérifier que tout se passe comme souhaité (créer, copier et détruire plusieurs objets).
(*) Note : on rappelle que contrairement à la mémoire dynamique (celle gérée par new et delete), la mémoire globale/static et la pile sont gérées automatiquement : les variables globales ou static sont détruites quand on sort du programme, les paramètres et variables locales des fonctions (pile) quand on sort de la fonction.


##8e étape. Créer des groupes
On va maintenant créer une nouvelle classe servant à contenir un groupe d'objets dérivant de la classe de base. Un groupe peut contenir un ensemble d'objets similaires (e.g. un groupe pour toutes les photos et un autre pour toutes les vidéos) ou pas (e.g. un groupe pour les photos et vidéos de vacances).
Pour ce faire on va utiliser la classe template list< > de la librairie standard qui permet de créer une liste d'objets (dont il faut préciser la classe entre les < >). Notez qu'il s'agit d'utiliser une classe template existante, pas d'en créer une nouvelle.
Deux stratégies sont possibles :
* soit créer une classe groupe qui contient une liste d'objets (la liste est alors une variable d'instance de la classe)
* soit créer une classe groupe qui hérite d'une liste d'objets (la liste est alors héritée de la classe parente)
La première stratégie nécessite de définir des méthodes dans la classe groupe pour gérer la liste. La seconde stratégie évite ce travail car elle permet d'hériter des méthodes de list. Elle est donc plus rapide à implémenter mais offre moins de contrôle (on ne choisit pas les noms des méthodes comme on veut et on hérite de toutes les méthodes de list y compris certaines qui sont peut-être inutiles ou pas souhaitables).
Pour aller plus vite, écrivez cette classe en utilisant la seconde stratégie. Définir les méthodes suivantes:
* un constructeur
* un accesseur qui renvoie le nom du groupe
* une méthode d'affichage qui affiche les attributs de tous les objets de la liste
Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.
Pour tester, créez quelques groupes dans main() en les peuplant de photos, videos ou films et en faisant en sorte que des objets appartiennent à plusieurs groupes. Appelez la fonction d'affichage des groupes pour vérifier que tout est OK.


##9e étape. Gestion automatique de la mémoire
Comme on l'a vu aux étapes 6 et 7, la gestion de la mémoire dynamique (celle allouée avec new en C++ et malloc() en C) est délicate. On risque en effet, soit de se retrouver avec des pointeurs pendants parce que l'objet qu'ils pointaient à été détruit ailleurs (cf. étape 6), soit avec des fuites mémoires parce l'on n'a pas détruit des objets qui ne sont plus pointés nulle part (cf. étape 7).
Les pointeurs pendants sont une source majeure de plantages ! Les fuites mémoires posent surtout problème si les objets sont gros (e.g. une image 1000x1000) et/ou si le programme s'exécute longtemps (e.g. un serveur Web tournant en permanence). On peut alors rapidement épuiser toute la mémoire disponible (noter cependant que la mémoire allouée de manière standard est toujours récupérée à la terminaison du programme).
Le ramasse miettes de Java et les les smart pointers avec comptage de références de C++ offrent une solution simple à ce problème : les objets sont alors automatiquement détruits quand plus aucun (smart pointer) ne pointe sur eux. Il ne faut donc jamais detruire avec delete un objet pointé par un smart pointer !
Le but de cette question est de remplacer les raw pointers (les pointeurs de base du C/C++) par des smart pointers non intrusifs dans les groupes de la question précédente. Les objets seront alors automatiquement détruits quand ils ne seront plus contenus par aucun groupe. Pour ce faire, utilisez les shared_ptr< > qui sont standard en C++11. Afin de vérifier que les objets sont effectivement détruits, modifiez leurs destructeurs de telle sorte qu'ils affichent un message sur le Terminal avant de "décéder".
Remarques
* Cette question ne porte pas sur les Films, qu'il n'est pas souhaitable de modifier.
* Pour simplifier l'expression, vous pouvez créer de nouveaux types grâce à using ou typedef en les déclarant dans le ou les headers appropriés:              using TrucPtr = std::shared_ptr<Truc>;
*              typedef std::shared_ptr<Truc> TrucPtr;
Enlevez des objets des groupes et vérifiez qu'ils sont effectivement détruits quand ils n'appartiennent plus à aucun groupe (et s'ils ne sont plus pointés par aucun autre smart pointer : noter que si p est un smart pointer p.reset() fait en sorte qu'il ne pointe plus sur rien)


##10e étape. Gestion cohérente des données
On va maintenant créer une classe qui servira à fabriquer et manipuler tous les objets de manière cohérente. Elle contiendra deux variables d'instance:
* une table de tous les objets multimédia
* une table de tous les groupes
Afin de permettre de retrouver efficacement les éléments à partir de leur nom, ces tables ne seront pas des tableaux ni des listes mais des tables associatives (cf. la classe template map). A chaque élement sera associé une clé de type string qui sera, suivant le cas, le nom de l'objet ou du groupe. Commencez tout d'abord par écrire cette classe, comme d'habitude dans un nouveau fichier. Comme précédemment, on utilisera les smart pointers afin de gérer la mémoire automatiquement.

Déclarer et implémenter des méthodes adéquates pour :
* Créér une Photo, une Vidéo, un Film, un Groupe et l'ajouter dans la table adéquate. Noter qu'il faut une méthode pour chaque type, renvoyant l'objet créé, afin de pouvoir le manipuler ultérieurement (c'est-à-dire appeler les fonctions déclarées pour ce type)
* Rechercher et Afficher un objet multimédia ou un groupe à partir de son nom, donné en argument. L'objectif sera d'afficher les attributs d'un objet ou le contenu d'un groupe dans le Terminal (s'il existe, sinon afficher un message d'alerte).
* Jouer un objet multimédia (à partir de son nom, donné en argument). Même chose que précédemment sauf que l'on appelle la méthode play() au lieu d'afficher les attributs.
Pour implémenter ces méthodes vous aurez probablement besoin des méthodes suivantes : map::operator[] (pour l'insertion), map::find() et map::erase(). Faites ensuite quelques essais dans main.cpp pour vérifier que ces méthodes fonctionnent correctement.

Les méthodes précédentes permettent d'assurer la cohérence de la base de données car quand on crée un objet on l'ajoute à la table adéquate. Par contre, ce ne sera pas le cas si on crée un objet directement avec new (il n'appartiendra à aucune table). Comment peut-on l'interdire, afin que seule la classe servant à manipuler les objets puisse en créer de nouveaux ?

Question additionnelle (vous pouvez passer cette question si vous êtes en retard) :
* Ajouter des méthodes pour Supprimer un objet multimédia ou un groupe à partir de son nom, donné en argument. L'élément doit être enlevé de la table adéquate et détruit s'il n'appartient plus à aucune table. De plus, lorsqu'on supprime un objet multimédia il faut d'abord l'enlever de tous les groupes dans lesquels il figure.
* De même que précédemment, il est préférable d'interdire à l'utilisateur de détruire un objet directetement en utilisant delete (c'est même pire car ca planterait le programme). Avec des raw pointers le principe serait le même que pour new. Avec des smart pointers c'est un peu plus compliqué, mais moins indispensable car on ne peut pas faire delete directement sur un smart pointer (mais comme toujours en C/C++ il existe toujours un moyen de faire ce qu'on veut, et éventuellement des bêtises!) Si ca vous interesse et que vous avez un compilateur à jour (donc pas celui des salles de TP) vous pouvez regarder comment faire.


##11e étape. Client / serveur
Cette étape vise à transformer votre programme C++ en un serveur qui communiquera avec un client qui fera office de télécommande. Dans cette question le client permettra d'envoyer des commandes textuelles. Plus tard, dans le TP suivant, vous réalisez une interface graphique Java Swing qui interagira avec le serveur de la même manière. Dans la réalité le serveur tournerait sur la set-top box et le client sur un smartphone ou une tablette.
Récuperez ces fichiers. Ils comprennent un client et un serveur ainsi que des fichiers utilitaires qui servent à faciliter la gestion des sockets. Pour les compiler il faut taper make -f Makefile-cliserv dans le Terminal. Lancez d'abord le serveur, puis (depuis un autre Terminal sur la même machine) le client et regardez le code correspondant.
* Le client crée une Socket qu'il connecte au serveur via la méthode connect(). Celle-ci précise à quelle machine et à quel port il faut se connecter. Par defaut le port est 3331 (le même que pour le serveur) et la machine est "localhost" (ce qui signifie que le client tourne sur la même machine que le serveur). La méthode connect() renvoie 0 si la connexion réussit et une valeur négative en cas d'erreur. S'il n'y a pas de firewall bloquant les connexions le client peut tourner sur une autre machine à condition de mettre le nom internet de la machine du serveur à la place de "localhost". Si la connexion est réalisée, le client lance une boucle infinie (pour quitter, taper ^C ou ^D ou quit) qui demande une ligne de commande à l'utilisateur puis l'envoie au serveur via la méthode writeLine(). Le client bloque jusqu'à la réception de la réponse retournée par le serveur qui est lue par la méthode readLine(). 
* Côté serveur, la méthode processRequest() est appelée chaque fois que le serveur reçoit une requête d'un client. Cette méthode récupère la requête via son 2e argument, effectue un traitement, puis retourne la réponse à retourner au client via son 3e argument. Pour l'instant ce traitement est minimal : la réponse est le message reçu précédé de "OK: ". 
Cette méthode est une fonction de callback (une fonction rappelée automatiquement) qui est spécifiée grâce à la méthode setCallback() de TCPServer. Cette méthode peut appartenir à n'importe quelle classe pourvu qu'elle ait les bons paramètres. Ceci est possible grâce aux pointeurs de méthodes et aux templates (les curieux pourront regarder comment setCallback() fonctionne dans tcpserver.h)

Le client et le serveur utilisent les classes "maison" Socket, ServerSocket et SocketBuffer qui permettent de faciliter l'utilisation des sockets Unix :
* Socket sert à créer une socket en mode TCP (par défaut) ou UDP
* ServerSocket est une socket spéciale qui permet à un serveur de détecter les demandes de connexion des clients
* SocketBuffer sert à simplifier la gestion des messages. Dans le cas général, les sockets TCP ne préservent pas les frontières entre les messages : un message peut arriver fragmenté ou au contraire être collé au message précédent. Les methodes writeLine() et readLine() de SocketBuffer résolvent ce problème grâce à l'addition d'une séquence de fin de ligne (par défaut le caractère \n) entre les messages (qui ne doivent donc pas contenir ce caractère !)
Noter aussi que :
* Le client et le serveur utilisent le protocole connecté TCP/IP qui permet déchanger un flux d'octets (stream en anglais) entre deux programmes. Ce protocole assure qu'il n'y a pas de paquets perdus et qu'ils arrivent toujours dans l'ordre.
* La connexion est persistante : quand on lance le client il se connecte au serveur et reste connecté jusqu'à la terminaison du client. Une autre possibilité serait d'établir une nouvelle connexion (et de la clore) à chaque échange client/serveur. On consommerait moins de ressources reseau mais ça ralentirait un peu la communication.
* Le dialogue est synchrone : le client envoie un message et bloque jusqu'à la réception de la réponse. Ca simplifie la programmation mais peut poser problème si la réponse est longue à arriver ou en cas d'erreur, en particulier si le client est une interface graphique (qui va donc se bloquer).
* Le serveur utilise des threads : il peut être connecté à plusieurs clients simultanément et la méthode processRequest() peut donc être appelée de manière concurrente par plusieurs clients. Ceci peut poser problème si plusieurs clients envoient en même temps des commandes qui modifient les données du serveur (mais pas si elles se contentent de les lire). Ce problème est réglé en utilisant des verrous (voir les indications dans processRequest()).

A vous de jouer :
En vous inspirant de server.cpp, adaptez votre propre programme pour qu'il joue le rôle du serveur de la set-top box et appelle les fonctions adéquates chaque fois qu'il recoit une requête du client. Pour ce faire il faudra définir un protocole de communication simple entre votre serveur et le client (client.cpp que l'on remplacera plus tard par une interface Java Swing). Il faut au moins pouvoir:
* rechercher un objet multimédia ou un groupe et afficher ses attributs sur la "télécommande" (c'est-à-dire, pour l'instant, les envoyer au client qui les affichera sur le Terminal)
* jouer un objet multimédia (l'objet doit être joué sur la "set-top box", c'est-à-dire le serveur).
Remarques
* Afin de conserver la version précédente du code dans le main() vous pouvez le mettre entre #ifdef VERSION_TRUC et #endif (il y a aussi #if et #else et il suffit d'écrire #define VERSION_TRUC en haut du fichier pour que ce soit cette version qui soit compilée).
* Il faut ajouter les fichiers cppsocket.cpp et tcperver.cpp à votre Makefile. Il faut également modifier la macro LDLIBS= de telle sorte que l'on ait LDLIBS= -lpthread dans le Makefile. Ceci sert à spécifier que l'on utilise cette bibliothèque système (c'est nécessaire pour certains OS, fait par défaut pour d'autres). Pensez aussi à mettre les bons namespaces (ceux dans server.cpp ou client.cpp).
* Votre méthode processRequest() devra pouvoir accéder aux données de la classe créée à la question précédente. Sachant que cette méthode peut appartenir à n'importe quelle classe, quelle est la solution la plus simple ?
* Vous aurez besoin de découper la requête récupérée par processRequest() en plusieurs mots. Pour ce faire vous pouvez utiliser les méthodes de string ou un stringstream. Un stringstream est un "buffer de texte" sur lequel on peut appliquer l'operateur >> ou la fonction getline() comme avec les fichiers ou l'entrée standard cin. La fonction getline() est pratique car elle permet de découper jusqu'à un caractère qu'on lui donne en argument (alors que l'operateur >> s'arrête dès qu'il trouve un espace).
* Une solution astucieuse pour envoyer les attributs des objets et des groupes au client est d'utiliser leurs méthodes d'affichage en leur passant en argument un stringstream. Elles écriront alors leurs attributs sur le stringstream qu'on peut ensuite convertir en string via sa méthode str(). Attention, comme dit précédemment, il ne faut pas envoyer les caractères \n ou \r (donc pas de endl) au client car ces caractères servent à délimiter les messages échangés entre le serveur et le client (dans les deux sens).
Questions additionnelles (vous pouvez passer ces questions si vous êtes en retard) :
* Vous pouvez rajouter d'autres commandes, par exemple chercher tous les objets commencant par ou contenant une séquence de caractères, ou étant d'un certain type, ou encore afficher toute la base ou détruire un objet ou un groupe.
* Un véritable serveur aurait probablement de nombreuses commandes. Afin d'accélérer la recherche des commandes vous pouvez utiliser une map contenant des pointeurs de méthodes ou mieux, des lambdas (la clé est le nom de la commande, l'attribut est la méthode ou la lambda correspondante).


##12e étape. Sérialisation / désérialisation
C++ ne propose pas en standard de moyen de sérialiser les objets de manière portable. On peut utiliser des extensions pour le faire (par exemple Cereal, Boost ou le toolkit Qt) ou juste l'implémenter "à la main" dans les cas simples. C'est ce que l'on va faire maintenant pour les tables d'objets multimédia. Notez qu'il est avantageux d'implémenter en même temps les fonctions d'écriture et de lecture, ces deux fonctionnalités dependant l'une de l'autre.
Ecrivez toutes les méthodes nécessaires en vous inspirant du cours puis testez les dans main() en sauvegardant puis en relisant la table d'objets multimédia (on laisse de côté les groupes). On rappelle:
* qu'il faut utiliser ofstream pour écrire sur un fichier, ifstream pour lire depuis un fichier et qu'il est nécessaire de vérifier si les fichiers ont pu être ouverts et de les fermer après usage à l'aide de leur méthode close().
* qu'il faut écrire les attributs des objets de telle sorte que l'on puisse ensuite les lire de manière non ambiguë. Faire en particulier attention aux chaînes de caractères, qui peuvent contenir des espaces. La fonction getline() résout ce problème.
* que pour lire - et donc créer - un objet multimédia à partir d'un fichier, il faut connaître sa classe. Il faut donc enregistrer le nom de la classe lors de l'écriture. Une solution est de définir pour chaque classe une méthode retournant son nom (sinon voir remarques plus bas).
* qu'il est souhaitable d'implémenter une fabrique d'objets permettant de créer les objets à partir du nom de leur classe.
* enfin, bien sûr il ne faut pas oublier les principes de l'orienté objet : chaque objet est le mieux placé pour savoir comment il doit être lu ou écrit sur un fichier et l'implémentation doit se faire en conséquence

Questions additionnelles
* Faire en sorte que l'on puisse utiliser les opérateurs operator<< et operator>> pour sérialiser et désérialiser les objets. Comme ils ne peuvent pas être déclarés comme des méthodes virtuelles des classes, il faut seulement les définir pour la classe de base et appeller une méthode virtuelle (redéfinie pour chaque sous-classe) pour faire le travail.
* Faites en sorte de pouvoir également (dé)sérialiser la table des groupes, en plus de la table des objets. Attention : ne pas dupliquer les objets (qui peuvent appartenir à plusieurs groupes !). Alternativement, vous pouvez utiliser une extension comme Cereal.

Remarques
La librairie standard de C++ fournit un moyen de récupérer les noms des classes via la fonction typeid() mais leur format dépend de l'implémentation. Avec g++ ce nom est encodé (par exemple N7Contact8Address2E pour Contact::Address) ce qui n'est pas très "user-friendly", ni très portable. La solution la plus simple est donc de faire comme conseillé plus haut.
Cependant, il existe des extensions dépendantes des implémentations qui permettent d'obtenir les noms décodés. Par exemple avec g++ on peut faire:
\#include <cxxabi.h>

bool demangle(const char* mangledName, std::string& realName) {
int status = 0;
char* s = abi::__cxa_demangle(mangledName, NULL, 0, &status);
realName = (status == 0) ? s : mangledName;
free(s);
return status;
}

std::string realname;
demangle(typeid(Photo).name(), realname);
cout << realname << endl;

ptr<Photo> p;
demangle(typeid().name(), realname);
cout << realname << endl;


##13e étape. Traitement des erreurs
La fiabilité des programmes repose sur la qualité du traitement des erreurs en cours d'exécution. Il faut en effet éviter de produire des résultats incohérents ou des plantages résultant de manipulations erronées. Jusqu'à présent nous avons négligé cet aspect dans les questions précédentes.
Exemples:
* si on crée plusieurs groupes ou objets ayant le même nom
* si on supprime un groupe ou un objet qui n'existe pas
* si le nom contient des caractères invalides
* si le tableau de durées d'un Film a une taille nulle ou inférieure à zéro
Il existe essentiellement deux stratégies pour traiter les erreurs. La première consiste à retourner des codes d'erreurs (ou un booléen ou un pointeur nul) lorsque l'on appelle une fonction pouvant produire des erreurs. La seconde consiste à générer des exceptions.

Dans le premier cas (codes d'erreurs), il est souhaitable que la fonction réalise une action "raisonnable" en cas d'erreur (par exemple ne rien faire plutôt que planter si on demande de supprimer un objet qui n'existe pas !). Cette solution peut poser deux problèmes:
* la propagation des erreurs entre les fonctions n'est pas toujours facile à traiter correctement (l'erreur pouvant se produire dans une fonction appelée dans une fonction elle-même appelée dans une autre fonction, et ainsi de suite).
* les programmeurs, toujours pressés, ont tendance à négliger les codes renvoyés. Ceci peut rendre imprévisible le comportement de programmes complexes et considérablement compliquer le deboguage.

La seconde solution (exceptions) est plus sûre dans la mesure où les erreurs doivent être obligatoirement traitées via une clause catch sous peine de provoquer la terminaison du programme (ou d'interdire la compilation en Java). Cependant, une utilisation trop intensive des exceptions peut compliquer le code et rendre son déroulement difficile à comprendre.
A vous de jouer ! Gerez les principaux cas d'erreurs comme bon vous semble, en utilisant la première ou la seconde stragégie, ou une combinaison des deux suivant la sévérité des erreurs. Mais faites en sorte que votre code soit cohérent par rapport à vos choix et justifiez les dans le rapport et/ou la documentation générée par Doxygen.
Remarque: pour créer de nouvelles classes d'exceptions en C++ il est préférable (mais pas obligatoire) de sous-classer une classe existante de la bibliothèque standard. L'exception runtime_error (qui dérive de la classe exception) est particulièrement appropriée et son constructeur prend en argument un message d'erreur de type string. Ce message pourra être récupéré au moment de la capture de l'exception grâce à la méthode what() (cf. l'exemple au bas de cette page).


#Deuxième partie : Javaswing

Le but de cet exercice est de créer une interface graphique Java/Swing qui permettra à terme d'interagir avec le logiciel déjà créé lors du TP C++/Objet. Comme précédemment, ce programme Java sera réalisé par étapes en ajoutant les fonctionnalités nécessaires petit à petit. Pensez à lire les "notes" ou "remarques" qui vous donneront des indications utiles avant de faire chaque étape. Vous pouvez utilisez l'IDE de votre choix pour programmer.


##1ere Etape: Fenêtre principale et quelques interacteurs
Créez une fenêtre principale (dérivant de JFrame) contenant une zone de texte multi-lignes (JTextArea) et trois boutons (JButton). Faites en sorte que, lorsqu'on les active, les deux premiers boutons ajoutent une ligne de texte (différente pour chaque bouton) à la zone de texte et que le dernier bouton termine l'application (cf. méthode exit(int)() de la classe System).

Notes :

Un JFrame est par défaut associé à un LayoutManager de type BorderLayout. Ceci permet un positionnement de ses enfants de type "points cardinaux" en appelant la méthode add() avec les arguments adéquats (voir la doc. de BorderLayout). Mettez par exemple la zone de texte dans la zone centrale et les boutons dans un conteneur JPanel lui-même situé dans la zone sud du JFrame.
Pour spécifier le comportement des boutons quand on les active vous pourrez vous inspirer de la "2e ou 3e stratégie" vues en cours (si vous avez le temps, faites les deux pour comparer).
Pensez à donner une taille suffisante au JTextArea en spécifiant un nombre de lignes et de colonnes adéquats à sa création.
N'oubliez pas d'appeler les méthodes suivantes de JFrame:
setDefaultCloseOperation(int) pour que la fermeture de l'interface entraîne la terminaison de l'application
pack() pour calculer la disposition spatiale des composants graphiques
setVisible(boolean) pour faire apparaître l'interface
Votre classe devra comprendre une variable serialVersionUID définie comme suit:
private static final long serialVersionUID = 1L;
Cette variable est réclamée par le compilateur pour préciser la version de la classe (1 dans ce cas). De plus cette classe doit etre publique et le fichier qui la contient doit avoir le même nom.
Documentez votre code au fur et à mesure de manière à pouvoir générer automatiquement la documentation grâce à JavaDoc ou Doxygen.
Lancez votre programme, cliquez plusieurs fois sur les deux premiers bouton, retaillez la fenêtre. Que constate-t'on ?

En fait, il est généralement nécessaire d'ajouter des ascenseurs à un JTextArea pour le rendre réellement utilisable. Pour ce faire, mettez ce composant dans un JScrollPane (en utilisant le constructeur adéquat de JScrollPane).


##2eme Etape: Menus, barre d'outils et actions
Nous allons maintenant rajouter une barre de menus (JMenuBar) comprenant un menu déroulant (JMenu) ainsi qu'une barre d'outils (JToolBar). Il faudra, comme de juste, placer la barre d'outils dans la zone nord de la fenêtre principale. La barre de menus sera ajoutée à la fenêtre via sa méthode setJMenuBar().

Le menu déroulant et la barre d'outils contiendront tous les deux les mêmes boutons que précédemment:

Une première solution consiste à procéder de la même manière qu'à l'étape précédente (à ceci près que les menus doivent contenir des JMenuItems et non des JButtons). Mais cette technique n'est pas particulièrement optimale car elle conduit à dupliquer les boutons qui sont dans les menus déroulants et ceux qui sont dans la barre d'outils alors qu'ils font la même chose.
Une autre possibilité (encouragée) est d'utiliser les Actions, ou, plus exactement, de créer des sous-classes de AbstractAction. Contrairement aux autres composants de Java Swing, les Actions peuvent être inclues simultanément dans plusieurs composants graphiques (dans notre cas, à la fois dans un JMenu et un JToolbar). Cette classe permet de spécifier toutes les caractéristiques d'un bouton (son nom et, optionnellement, une image, un mnémonique, un raccourci clavier, l'état du bouton s'il en a un) ainsi que son comportement en redéfinissant sa méthode actionPerformed().
Notes

On rappelle qu'il ne doit y avoir qu'une seule classe publique dans un fichier Java. Cependant vous pouvez définir d'autres classes non publiques si cela s'avère nécessaire.
Pour les utilisateurs de MacOSX : pour que les barres de menus apparaissent comme d'habitude sur cette plate-forme il faut faire:
System.setProperty("apple.laf.useScreenMenuBar", "true");


##3eme Etape: Interaction client/serveur
Cette étape vise à faire communiquer votre programme Java avec le programme C++, faisant office de serveur, que vous avez réalisé aux TPs précédents. Tout d'abord, téléchargez le programme Client.java. Ce programme fait la même chose que le programme client.cpp vu à la question 11 du TP C++. Compilez le et vérifiez qu'il interagit correctement avec le serveur C++.

Adaptez le code que vous avez écrit à l'étape précédente pour créer une interface graphique qui interagisse avec le serveur C++. Les fonctionnalités souhaitées sont les mêmes qu'à la question 13 du TP C++ : pouvoir rechercher un objet multimédia (l'affichage devant se faire sur l'interface graphique Java Swing qui joue le rôle de télécommande), et pouvoir "jouer" un objet multimédia (sur le serveur C++, qui fait office de "set-top box").

Notes
Vous pouvez bien sûr rajouter toute commande qui vous semble utile pour une télécommande !
Si vous avez le temps, vous pouvez améliorer l'interface pour la rendre plus facile à utiliser en exploitant les nombreuses possibilités offertes par Java Swing. Outre des JTexField vous pourrez par exemple utiliser des onglets (JTabbedPane) ou des boîtes de dialogue (JDialog) ou encore des boutons exclusifs (cf. JRadioButton et ButtonGroup).
4eme Etape (obligatoire): Créer un Makefile
Vous avez probablement utilisé un IDE qui a créé des fichiers un peu partout. C'est bien pour développer mais pas forcément pour déployer sur d'autres machines et encore moins ... pour corriger !

On vous demande dans cette question, d'adapter ce Makefile qui va permettre de compiler puis d'executer automatiquement le programme Java (la télécommande de l'étape 3) juste en tapant make run dans le Terminal.
