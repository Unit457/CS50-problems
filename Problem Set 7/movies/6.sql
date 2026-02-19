-- Calcula o average rating dos filmes
SELECT AVG(rating)
FROM ratings
-- (Relaciona as tabelas ratings e movies através do id dos filmes)
JOIN movies ON movies.id = ratings.movie_id
-- Que saíram em 2012
WHERE movies.year = 2012;
