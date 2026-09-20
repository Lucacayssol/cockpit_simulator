# J'ai choisi de rassembler ici mes quelques périphériques pour Flight Simulator ou des jeux de F1 imprimé en 3d pour faciliter la taches aux suivants
Actuellement, j'ai construit un HOTAS, une manette des gaz (throttle), et un Rudder.
## Simulation de vol
Pour construire ces appareils, vous aurez globalement besoin d'Arduinos (Pro Micro conseillés, Leonardo possible) et de ressorts. Un lot de potentiomètre est aussi nécessaires. Vous aurez besoin d'autres pièces selon ce que vous voulez construire.
### HOTAS
J'ai utilisé ce modèle : https://www.thingiverse.com/thing:4576634 en utilisant les plus gros roulement (17*6mm). Jai trouvé que coller les capteurs à effet Hall étaient un peu fastidieux. J'ai donc redessiné légèrement l'axe (dispo sous le nom "AxeC.3mf"). Concernant le code, je l'inclus aussi. J'ai rajouté une fonction : un appui long sur la gâchette change la deadzone. Particulièrement adapté pour changer entre Flight Simulator et Farming Simulator. Je n'ai par contre pas installé les quatre boutons du haut, ni ceux de la base
### Throttle
Voici le modèle : https://www.thingiverse.com/thing:6994616
J'ai ajoutés des plaques de chaque coté des engrenage pour augmenter le frottement ainsi qu'une vis entre le manche et l'engrenage pour limiter le jeu
### Rudder
Voici le modèle pour fonctionner avec ce rudder : https://www.thingiverse.com/thing:4578174 J'ai utilisé une tige filetée pour relier la base aux pédales. Le reste : Arduino Pro Micro, Potentiomètre et ressort de tension (Aliexpress)
## Simulation de course
### Volant
J'ai choisi de partir sur une base existante : https://www.printables.com/model/1236930-v2-xbox-series-xs-controller-racing-wheel-100-3d-p
Ce modèle coute cependant 6$. Je n'ai personnellement pas réussi à le faire fonctionner directement avec la manette de Xbox, mais j'ai décidé d'utiliser un gyroscope (pour des questions de facilités d'installation). Je vais donc revoir le volant car je le trouve étonnamment complexe avec ces pièces vissées et collées. Étant donnée que je n'ai plus de manette, je vais concevoir une simple plaque.
