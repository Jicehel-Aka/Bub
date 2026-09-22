# update.py — genere Levels.cpp depuis la version HTML5 (index.html).
#
# Usage : placer index.html a cote de ce script, lancer `python update.py`,
# puis copier le Levels.cpp produit dans ../main/game/Levels.cpp
# Le format emis ( Difficulty:: / bool experimental / rows[8] ) doit rester
# synchrone avec main/game/Levels.h.

import re

difficulty_map = {
    0:"Beginner",
    1:"Beginner",
    2:"Easy",
    3:"Easy",
    4:"Intermediate",
    5:"Intermediate",
    6:"Advanced",
    7:"Advanced",
    8:"Experimental",
    9:"Experimental"
}

with open("index.html","r",encoding="utf8") as f:
    txt = f.read()

pattern = re.compile(
    r'difficulty:\s*(\d+).*?level:\s*\[(.*?)\]',
    re.S
)

levels = pattern.findall(txt)

with open("Levels.cpp","w",encoding="utf8") as out:

    out.write('#include "Levels.h"\n\n')
    out.write("const LevelDef LEVELS[] =\n{\n")

    for diff,data in levels:

        rows = re.findall(r'"([^"]*)"',data)

        while len(rows) < 8:
            rows.append("")

        rows = [r.ljust(8)[:8] for r in rows]

        d = difficulty_map[int(diff)]
        experimental = "true" if int(diff) >= 8 else "false"

        out.write("    {\n")
        out.write(f"        Difficulty::{d},\n")
        out.write(f"        {experimental},\n")
        out.write("        {\n")

        for row in rows:
            out.write(f'            "{row}",\n')

        out.write("        }\n")
        out.write("    },\n\n")

    out.write("};\n\n")
    out.write(
        "const uint16_t LEVEL_COUNT = "
        "sizeof(LEVELS)/sizeof(LevelDef);\n"
    )