open Rationale;

type situation =
  | LiveNeighbours(bool, int);

type grid = list(list(bool));

type colourGrid = list(list(int));

/* why is this function not data last? */
let optBindFlip = Function.flip(Option.bind);

/* getFromCoord :: int -> int -> list(list(a)) -> Option(a) */
let getFromCoord = (x: int, y: int, grid) =>
  RList.nth(y, grid) |> optBindFlip(RList.nth(x));

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