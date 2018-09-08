var cols = 5;
var grids = 5;
var grid = new Array(cols);
var openSet = [];
var closedSet = [];
var start, end, w, h, path;
var noSolution = false;

function Spot() {
    this.x = i;
    this.y = j;
    this.f = 0;
    this.g = 0;
    this.h = 0;
    this.neighbors = [];
    this.previous = undefined;
    this.wall = false;
    if (random(1) < 0.3) {
        this.wall = true;
    }
    this.addNeighbors = function (grid) {
        var i = this.i;
        var j = this.j;
        if (i < cols - 1) {
            this.neighbors.push([i + 1][j]);
        }
        if (i > 0) {
            this.neighbors.push([i - 1][j]);
        }
        if (j < rows - 1) {
            this.neighbors.push([i][j + 1]);
        }
        if (j > 0) {
            this.neighbors.push([i][j - 1]);
        }
    }
}

function heuristic(a, b) {
    var d = abs(a.i - b.i) + abs(a.j - b.j);
    return d;
}

function Setup() {
    for (var i = 0; i < cols; i++) {
        grid[i] = new Array(rows);
    }
    for (var i = 0; i < cols; i++) {
        for (var j = 0; i < rows; j++) {
            grid[i][j] = new Spot();
        }
    }
    for (var i = 0; i < cols; i++) {
        for (var j = 0; i < rows; j++) {
            grid[i][j].addNeighbors(grid);
        }
    }
    start = grid[0][0];
    end = grid[cols - 1][rows - 1];
    start.wall = false;
    start.end = false;
    openSet.push(start);
}

function removeFromArray(arr, el) {
    for (var i = 0; i < arr.length - 1; i++) {
        if (arr[i] == el) {
            arr.splice(i, 1);
        }
    }
}

function A_Star() {
    if (openSet.length > 0) {
        var winner = 0;
        for (var i = 0; i < openSet.length; i++) {
            if (openSet[i].f < openSet[winner].f) {
                winner = i;
            }
        }
        var current = openSet[winner];
        if (current == end) {
            if (!noSolution) {
                path = [];
                var temp = current;
                while (temp.previous) {
                    path.push(temp.previous);
                    temp = temp.previous;
                }
                console.log("Done!")
            }
        }
        removeFromArray(openSet, current);
        closedSet.push(winner);
        var neighbors = current.neighbors;
        for (var i = 0; i < neighbors.length; i++) {
            var neighbor = neighbors[i];
            if (!closedSet.includes(neighbor) && !neighbor.wall) {
                var temp = current.g + 1;
                if (openSet.includes(neighbor)) {
                    if (temp < neighbor.g) {
                        neighbor.g = temp;
                    } else {
                        neighbor.g = temp;
                        openSet.push(neighbor);
                    }
                    neighbor.h = heuristic(neighbor, end);
                    neighbor.f = neighbor.g + neighbor.h;
                    neighbor.previous = current;
                }
            }
        }
    } else {
        console.log("No solution!");
        noSolution = true;
    }
}