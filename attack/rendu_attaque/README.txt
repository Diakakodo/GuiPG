Lucas Barbay
15/05/15

Vous trouverez dans cette archive :
- La clef qui a servi de test pour l'attaque (clef_pub, clef_sec)
- La clef générée par le script possédant le même key_id que la première clef : A06B652D.gpg
- Le CDR mis à jour.


Vous pouvez importer les deux clefs et constater que leur key_id est le même.
La première clef a été généré par GPG, elle peut donc effectuer des opérations cryptographiques.

Lorsque vous importerez la deuxième, vous constaterez qu'elle ne contient que sa propre signature en guise d'uid.
Pour pouvoir utiliser cette clef, il faut donc ajouter une date de validation : gpg --edit-key A06B652D expire
Puis il vous faudra ajouter une phrase de passe car la création se fait sans. (gpg --edit-key A06B652D passwd).
Enfin la dernière étape consiste à ajouter une sous-clef pour les opérations de chiffrement. (gpg --edit-key A06B652D addkey)

Vous avez maintenant deux clefs valide dans gpg avec le même key_id.

L'usage du script est : 

./attaque "user_id" key_id key_size

Lorsque vous entrerez le user_id, il faudra mettre l'email entre chevrons pour qu'il soit pris en compte par gpg lors de son importation.
Les trois paramètres sont obligatoires pour utiliser le script.