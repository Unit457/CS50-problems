-- Lista o nome de todos os songs
SELECT name
from songs;

-- Lista o nome de todos os songs, ordenando-os pelo tempo (menor pro maior)
SELECT name
FROM songs
ORDER BY tempo ASC;

-- Lista o nome dos 5 maiores songs (maior pro menor)
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;

-- Lista o nome de todos songs que possuam danceability, energy e valence maior que 0.75
SELECT name
FROM songs
WHERE danceability > 0.75 AND energy > 0.75 AND valence > 0.75;

-- Lista o average energy de todos os songs
SELECT AVG(energy)
FROM songs;

-- Lista os nomes de todas as músicas que possuam artist_id igual ao id do artista com name 'Post Malone'
SELECT name
FROM songs
WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');

-- Lista o average energy de todos os songs do Drake
SELECT AVG(energy)
from songs
-- Realizando um join com a tabela artistas utilizando "devem possuir o mesmo id" como parâmetro
JOIN artists ON songs.artist_id = artists.id
-- Aonde o nome do artista for 'Drake'
WHERE artists.name = 'Drake';

-- Lista o nome de todos os songs que possuam 'feat.' no nome
SELECT name
FROM songs
WHERE name LIKE '%feat.%';
