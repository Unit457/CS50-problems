-- Lista o nome de todos os songs que possuam 'feat.' no nome
SELECT name
FROM songs
WHERE name LIKE '%feat.%';
