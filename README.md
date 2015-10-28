# PES9EETAAS

Projet Électronique S9.

Le but de ce projet est d'interfacer une carte Beagleboard XM1 avec des cartes FPGA auxquelles sont reliés divers capteurs dont on fait l'acquisition de données.
Les données rapatriés le sont par le biais du protocole Zigbee, et le tout est affiché sur une interface web. 

Participants au projet : Erwin ANDRÉ, Thomas AUDRAIN & Éric SCHAFER




NB1 -> Pour générer facilement des trames ZigBee, voir ce site : http://ftp1.digi.com/support/utilities/digi_apiframes2.htm

NB2 -> Pour compiler, se placer dans un des dossiers contenant (au moins) les 3 dossiers include, src et main. Puis effacer les fichiers CMakeCache.txt et cmake_install.cmake.
Enfin faire la commande "cmake ." (dans ce dossier et sans les guillemets). Un "make" suffira à compiler. Lancer le programme.
