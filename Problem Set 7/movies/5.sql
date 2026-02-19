-- Lista o título e o ano dos filmes
SELECT title, year
FROM movies
-- Que tenham "Harry Potter and the" no começo de seu título
WHERE title LIKE 'Harry Potter and the%'
-- Ordando-os pelo ano do mais antigo até o menos antigo
ORDER BY year ASC;
