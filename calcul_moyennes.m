M=csvread('vorace-resultats.csv');
id_fichier=fopen('vorace_resultats_moyens.csv','a');
if(id_fichier==-1)
        error('Probleme lors de la creation');
end

for i=0:19
    temps_moyen=sum(M(i*10+(1:10),1))/10;
    n=M(i*10+1,2);
    m=M(i*10+1,3);
    volume_restant_moyen=sum(M(i*10+(1:10),4))/10;
    fprintf(id_fichier,'%i % i %.2f %.2f \n',n,m,temps_moyen,volume_restant_moyen);
end
fclose(id_fichier);
