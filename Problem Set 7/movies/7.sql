-- Lista o rating e o título dos filmes
SELECT title, rating
FROM movies
-- (Relaciona as tabelas movies e ratings através do id dos filmes)
JOIN ratings ON movies.id = ratings.movie_id
-- Que saíram em 2010
WHERE year = 2010
-- Ordenando-os pela rating (melhor pra pior) e secundariamente pelo título (alfabeticamente)
ORDER BY rating DESC, title ASC;
