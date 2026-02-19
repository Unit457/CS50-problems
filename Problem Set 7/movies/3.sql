-- Lista os títulos dos filmes
SELECT title
FROM movies
-- Que saíram em ou depois de 2018
WHERE year >= 2018
-- Ordenando-os pelo título em ordem alfabética
ORDER BY title ASC;
