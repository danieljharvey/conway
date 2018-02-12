open Jest;

let testGrid = [[true, true, true], [false, false, false], [true, true, true]];

describe("Count neighbours", () => {
  Expect.(
    test("in the middle", () =>
      expect(Life.countNeighbours(1, 1, testGrid)) |> toBe(6)
    )
  );
  Expect.(
    test("at the top left", () =>
      expect(Life.countNeighbours(0, 0, testGrid)) |> toBe(2)
    )
  );
  Expect.(
    test("at the bottom middle", () =>
      expect(Life.countNeighbours(1, 2, testGrid)) |> toBe(3)
    )
  );
});

describe("Get from coord", () => {
  Expect.(
    test("when it exists", () =>
      expect(Life.getFromCoord(0, 0, testGrid)) |> toEqual(Some(true))
    )
  );
  Expect.(
    test("when it doesn't exist", () =>
      expect(Life.getFromCoord(3, 4, testGrid)) |> toEqual(None)
    )
  );
});