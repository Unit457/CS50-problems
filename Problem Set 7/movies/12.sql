-- Lista os títulos dos filmes
SELECT title
FROM movies
-- Que tiverem o id correspondente a algum dos:
WHERE id IN (
    -- ids dos filmes
    SELECT movie_id
    FROM stars
    -- que Bradley Cooper participou
    WHERE person_id = (SELECT id FROM people WHERE name = 'Bradley Cooper')
    -- que sejam os mesmos dos
    INTERSECT
    -- ids dos filmes
    SELECT movie_id
    FROM stars
    -- que Jennifer Lawrence participou
    WHERE person_id = (SELECT id FROM people WHERE name = 'Jennifer Lawrence')
);
