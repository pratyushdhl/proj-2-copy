#!/usr/bin/env python3
"""Purpose: exercise M1 behavior through the menu. Author: Codex (AI assistance)."""
from pathlib import Path
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
BINARY = Path(sys.argv[1]).resolve() if len(sys.argv) > 1 else ROOT / 'build/campus'
NUMBER = 0


def run(description, data, commands, expected, absent=(), counts=()):
    """Run one scenario, verify observable results, and print reproducible evidence."""
    global NUMBER
    NUMBER += 1
    args = [str(BINARY)] + ([] if data is None else [str(data)])
    result = subprocess.run(args, input=commands, text=True, capture_output=True,
                            cwd=ROOT, timeout=10)
    output = result.stdout
    assert result.returncode == 0, result.stderr
    assert not result.stderr, result.stderr
    for value in expected:
        assert value in output, f'{description}: missing {value!r}\n{output}'
    for value in absent:
        assert value not in output, f'{description}: unexpected {value!r}'
    for value, count in counts:
        assert output.count(value) == count, (description, value, output.count(value))
    # Exact expected strings serve as observations, not independently calculated totals.
    print(f'Test {NUMBER}: {description}')
    print('Input directory:', data if data is not None else 'data/ (default)')
    print('Menu input:', repr(commands))
    print('Expected:', repr(expected), 'Absent:', repr(absent), 'Counts:', repr(counts))
    print('Actual: exit 0; all expected output matched; exclusions and counts verified.')
    print('Result: PASS\n')
    return output


# The supplied files must remain byte-identical even after menu additions.
original = {p: p.read_bytes() for p in (ROOT / 'data').iterdir() if p.is_file()}
run('Sample loading, file order, duplicate facility names, graph degrees', None,
    '1\n3\n4\n10\n', [
        'buildings.txt: 7 accepted, 0 rejected\nconnections.txt: 6 accepted, 0 rejected\n'
        'facilities.txt: 10 accepted, 0 rejected (hash capacity 11, entries 10, collisions 1)\n'
        'departments.txt: 7 accepted, 0 rejected',
        'F005 | Room 101 | Engineering Building | Classroom',
        'F007 | Room 101 | Business Building | Classroom',
        'Total facilities: 10', 'Observatory:\n\t(no connections)',
        'Library              | 2', 'Student Union        | 3',
        'Science Building     | 2', 'Engineering Building | 1',
        'Business Building    | 2', 'Gym                  | 2', 'Observatory          | 0',
        'Total buildings: 7', 'Total connections: 6'])
run('ID lookup: found, lowercase, invalid, absent', None,
    '2\nF004\n2\n f004 \n2\n004\n2\nf999\n10\n', [
        'F004 | Computer Lab A | Science Building | Computer Lab',
        'Invalid format: an ID is F followed by exactly three digits.',
        'Not found: no facility with ID F999'], counts=[('F004 | Computer Lab A', 2)])
run('BFS visit order, cycles, isolated component, unknown start', None,
    '5\n library \n5\nObservatory\n5\nUnknown Hall\n10\n', [
        'Library (distance 0)\nStudent Union (distance 1)\nBusiness Building (distance 1)\n'
        'Science Building (distance 2)\nGym (distance 2)\nEngineering Building (distance 3)',
        'Reachable: 6 of 7 buildings', 'Observatory (distance 0)',
        'Reachable: 1 of 7 buildings', 'Unknown or blank building: Unknown Hall'])
run('Department root, non-root, missing search, hierarchy, preorder', None,
    '7\n UNIVERSITY \n7\n computer science \n7\nMissing\n8\n9\n10\n', [
        'Department: University\nParent: None\nDirect children: 2\nDepth: 0',
        'Department: Computer Science\nParent: College of Engineering\nDirect children: 0\nDepth: 2',
        'Department not found: Missing',
        'University\n    College of Engineering\n        Computer Science\n        Electrical Engineering\n'
        '    College of Science\n        Mathematics\n        Physics',
        'University\nCollege of Engineering\nComputer Science\nElectrical Engineering\nCollege of Science\nMathematics\nPhysics'])
run('Menu addition, unknown parent, duplicate name, in-memory persistence', None,
    '6\nNew Department\nUnknown Parent\n6\n UNIVERSITY \nUniversity\n'
    '6\nNew Department\n college of science \n7\nnew department\n10\n', [
        'Error: unknown parent: Unknown Parent', 'Error: duplicate department: UNIVERSITY',
        'Department added: New Department',
        'Department: New Department\nParent: College of Science\nDirect children: 0\nDepth: 2'])
run('Invalid menu input, blank names, spaces, repeated recovery', None,
    '\nletters\n-1\n11\n2 extra\n999999999999999999999\n5\n \n6\n \n'
    '7\n \n6\nChild\n \n2\n \n5\n Student Union \n0\n', [
        'Department name cannot be blank.', 'Parent name cannot be blank.',
        'Invalid format: an ID is F followed by exactly three digits.',
        'From Student Union:', 'Reachable: 6 of 7 buildings'],
    counts=[('Invalid menu input.', 6)])
run('Collision fixture and rejected duplicate keep original record and count',
    'testdata/collision', '1\n2\nf001\n2\nf013\n10\n', [
        'Warning: facilities.txt:4: duplicate facility ID: F001',
        'facilities.txt: 2 accepted, 1 rejected (hash capacity 11, entries 2, collisions 1)',
        'F001 | First Record | Library | Library', 'F013 | Colliding Record | Library | Library'],
    absent=['Rejected Duplicate'])

with tempfile.TemporaryDirectory(prefix='campus-m1-') as temporary:
    directory = Path(temporary)
    files = {
        'buildings.txt': '  # comment\r\n\r\n Library \r\n library\r\nStudent Union\r\nBad|Extra\r\nObservatory',
        'connections.txt': '# comment\nLibrary|Student Union\nstudent union|LIBRARY\nLibrary|Missing\nLibrary|Library\nLibrary\nLibrary|Student Union|Extra',
        'facilities.txt': '# comment\n f001 | Room #5 | library | Computer Lab \r\nF001|Later|Library|Other\nF002|Unknown|Missing|Other\n004|Bad|Library|Other\nF003|Too few|Library\nF004|Too|Library|Other|Extra\nF005||Library|Other\nF006|Second|STUDENT UNION|computer lab',
        'departments.txt': '# comment\nBad Root|Missing\n University | none \r\nChild|Unknown\nCollege of Science|UNIVERSITY\ncollege of science|University\nExtra|University|Bad\nBlank|\nSecond Root|NONE\nPhysics|College of Science'
    }
    for name, content in files.items():
        (directory / name).write_bytes(content.encode())
    run('Validation, CRLF, whitespace, comments, final line without newline', directory,
        '1\n4\n5\nstudent union\n7\nphysics\n10\n', [
            'buildings.txt: 3 accepted, 2 rejected', 'connections.txt: 1 accepted, 5 rejected',
            'facilities.txt: 2 accepted, 6 rejected', 'departments.txt: 3 accepted, 6 rejected',
            'Warning: buildings.txt:4: duplicate building:',
            'Warning: buildings.txt:6: expected one nonempty field',
            'Warning: connections.txt:3: duplicate connection:',
            'Warning: connections.txt:4: unknown building: Missing',
            'Warning: connections.txt:5: self-connection:',
            'Warning: facilities.txt:3: duplicate facility ID: F001',
            'Warning: facilities.txt:4: unknown building: Missing',
            'Warning: departments.txt:4: unknown parent: Unknown',
            'F001 | Room #5 | Library | Computer Lab',
            'F006 | Second | Student Union | Computer Lab',
            'Total connections: 1', 'Reachable: 2 of 3 buildings',
            'Department: Physics\nParent: College of Science\nDirect children: 0\nDepth: 2'],
        absent=['Later |', 'Second Root\n'])
    # No final newline is used above, so every file's final accepted record is checked.
    for name in files:
        (directory / name).write_text('')
    run('Empty structures and adding the first root without a parent prompt', directory,
        '1\n2\nF001\n3\n4\n5\nLibrary\n7\nMissing\n8\n9\n'
        '6\nNew University\n7\nnew university\n8\n9\n10\n', [
            'buildings.txt: 0 accepted, 0 rejected', 'connections.txt: 0 accepted, 0 rejected',
            'facilities.txt: 0 accepted, 0 rejected (hash capacity 11, entries 0, collisions 0)',
            'departments.txt: 0 accepted, 0 rejected', 'No facilities available.',
            'Total facilities: 0', 'No buildings exist.', 'Total buildings: 0',
            'Total connections: 0', 'No departments available.',
            'Department added: New University',
            'Department: New University\nParent: None\nDirect children: 0\nDepth: 0'],
        absent=['Enter parent department:'])
    for name in files:
        (directory / name).unlink()
    run('All four missing files continue with zero summaries', directory, '1\n8\n0\n', [
        'cannot open ' + str(directory / name) for name in files] + [
        'facilities.txt: 0 accepted, 0 rejected (hash capacity 11, entries 0, collisions 0)',
        'No facilities available.', 'No departments available.'])
    # A separate missing file must not prevent later independent loads.
    for name in files:
        if name != 'connections.txt':
            (directory / name).write_bytes(original[ROOT / 'data' / name])
    run('Missing connections alone preserves buildings and later files', directory,
        '4\n5\nLibrary\n10\n', [
            'Error: cannot open ' + str(directory / 'connections.txt'),
            'buildings.txt: 7 accepted, 0 rejected', 'connections.txt: 0 accepted, 0 rejected',
            'facilities.txt: 10 accepted, 0 rejected', 'departments.txt: 7 accepted, 0 rejected',
            'Total connections: 0', 'Reachable: 1 of 7 buildings'])
    # Accepted-only collision counts: remove the duplicate, compare the diagnostic.
    for name in files:
        (directory / name).write_bytes((ROOT / 'testdata/collision' / name).read_bytes())
    (directory / 'facilities.txt').write_text('F001|First Record|Library|Library\nF013|Colliding Record|Library|Library\n')
    run('Same collision count with no duplicate attempt', directory, '0\n', [
        'facilities.txt: 2 accepted, 0 rejected (hash capacity 11, entries 2, collisions 1)'])

run('EOF at menu exits cleanly', None, '', ['departments.txt: 7 accepted, 0 rejected'])
run('EOF during a name prompt exits cleanly', None, '5\n', ['Enter start building:'])
assert all(p.read_bytes() == content for p, content in original.items())
print(f'{NUMBER} scenarios passed. All original data/ files remained byte-identical.')
