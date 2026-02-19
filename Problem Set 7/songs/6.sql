-- Lista os nomes de todas as músicas que possuam artist_id igual ao id do artista com name 'Post Malone'
SELECT name
FROM songs
WHERE artist_id = (SELECT id FROM artists WHERE name = 'Post Malone');
