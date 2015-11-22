M=csvread('dynamique-resultats.csv');
id_fichier=fopen('dynamique_resultats_moyens.csv','a');
if(id_fichier==-1)
        error('Probleme lors de la creation');
end

for i=1:20
    temps_moyen=sum(M(2*i,3))/10;
    n=10;
    m=M(2*i,2);
    volume_restant_moyen=100-(sum(M(2*i+1,3))/10);
    fprintf(id_fichier,'%i, % i, %.2f, %.2f \n',n,m,temps_moyen,volume_restant_moyen);
end
for j=21:30
    temps_moyen=sum(M(2*i,3))/10;
    n=32;
    m=M(2*i,2);
    volume_restant_moyen=100-(sum(M(2*i+1,3))/10);
    fprintf(id_fichier,'%i, % i, %.2f, %.2f \n',n,m,temps_moyen,volume_restant_moyen);
end
fclose(id_fichier);
