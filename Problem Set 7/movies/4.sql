-- Conta os filmes
SELECT COUNT(movie_id)
FROM ratings
-- Que tem a rating igual a 10
WHERE rating = 10;
