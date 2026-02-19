-- Lista o average energy de todos os songs do Drake
SELECT AVG(energy)
from songs

-- Realizando um join com a tabela artistas utilizando "devem possuir o mesmo id" como parâmetro
JOIN artists ON songs.artist_id = artists.id

-- Aonde o nome do artista for 'Drake'
WHERE artists.name = 'Drake';
