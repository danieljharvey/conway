type situation =
  | LiveNeighbours(bool, int);

let safeListGet = (n, list) =>
  n < 0 || n > List.length(list) - 1 ? None : Some(List.nth(list, n));

/* getFromCoord :: int -> int -> list(list(a)) -> Option(a) */
let getFromCoord = (x: int, y: int, grid) =>
  switch (safeListGet(y, grid)) {
  | None => None
  | Some(items) => safeListGet(x, items)
  };

let getNeighbours = (x, y, grid) =>
  List.map(
    nY => List.map(nX => getFromCoord(nX, nY, grid), [x - 1, x, x + 1]),
    [y - 1, y, y + 1]
  )
  |> List.flatten;

let countNeighbours = (x, y, grid) =>
  getNeighbours(x, y, grid)
  |> List.filter(i =>
       switch i {
       | Some(true) => true
       | _ => false
       }
     )
  |> List.length;

let isLive = (x, y, grid) =>
  switch (getFromCoord(x, y, grid)) {
  | Some(true) => true
  | _ => false
  };

let getNextItem = (x, y, grid) =>
  switch (LiveNeighbours(isLive(x, y, grid), countNeighbours(x, y, grid))) {
  | LiveNeighbours(false, n) => n == 3 ? true : false
  | LiveNeighbours(true, n) => n == 2 || n == 3 ? true : false
  };

let boardMove = grid =>
  List.mapi(
    (y, row) => List.mapi((x, _) => getNextItem(x, y, grid), row),
    grid
  );