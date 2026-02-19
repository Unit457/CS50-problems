-- Lista o nome dos 5 maiores songs (maior pro menor)
SELECT name
FROM songs
ORDER BY duration_ms DESC
LIMIT 5;
