import sys

vul_libs = set(input().split())
direct_dep_libs = set(input().split())
deps = dict()

for line in sys.stdin:
    if line == "\n":
        continue
    splitted_line = line.split()
    if len(splitted_line) > 1:
        if len(vul_libs) >= len(direct_dep_libs):
            if splitted_line[0] in deps.keys():
                t1 = set().union(deps[splitted_line[0]], splitted_line[1:])
                deps.update({splitted_line[0]: t1})
            else:
                deps.update({splitted_line[0]: set(splitted_line[1:])})
        else:
            for lib in splitted_line[1:]:
                if lib in deps.keys():
                    deps[lib].add(splitted_line[0])
                else:
                    deps.update({lib: set(splitted_line[0].split())})


def travel_iterative(reverse=False, start_line=direct_dep_libs, finish_line=vul_libs):
    for lib in start_line:
        stack = list()
        visited_libs = set()
        path = ""
        count_of_words = 0
        stack.append((1, lib))
        while len(stack) != 0:
            pair = stack.pop()
            vertex = pair[1]
            curr_level = pair[0]

            splitted_path = path.split()
            for i in range(count_of_words - curr_level + 1):
                if not reverse:
                    visited_libs.remove(splitted_path[-1])
                    splitted_path.pop()
                else:
                    visited_libs.remove(splitted_path[0])
                    splitted_path.pop(0)
                count_of_words -= 1
            path = ' '.join(splitted_path)

            if vertex not in visited_libs:
                if len(path) == 0:
                    path = vertex
                else:
                    if not reverse:
                        path += " " + vertex
                    else:
                        path = vertex + " " + path
                count_of_words += 1
                visited_libs.add(vertex)
                if vertex in finish_line:
                    print(path)
                if vertex in deps.keys():
                    for dep_lib in deps[vertex]:
                        stack.append((curr_level + 1, dep_lib))


if len(vul_libs) >= len(direct_dep_libs):
    travel_iterative()
else:
    travel_iterative(True, vul_libs, direct_dep_libs)