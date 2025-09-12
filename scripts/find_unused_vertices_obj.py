### GPT CODE ###
import argparse

def parse_obj_file(file_path):
    vertices = []
    faces = []
    
    with open(file_path, 'r') as f:
        for line in f:
            line = line.strip()
            if line.startswith('v '):
                vertices.append(line)
            elif line.startswith('f '):
                faces.append(line)
    
    return vertices, faces


def get_used_vertex_indices(faces):
    used_indices = set()

    for face in faces:
        parts = face.split()[1:]
        for part in parts:
            idx = part.split('/')[0]
            if idx:
                used_indices.add(int(idx))
    
    return used_indices


def print_unused_vertices(vertices, used_indices):
    total = len(vertices)
    all_indices = set(range(1, total + 1))
    unused_indices = sorted(all_indices - used_indices)

    print(f"\n=== Análise de uso de vértices ===")
    print(f"Total de vértices: {total}")
    print(f"Vértices usados nas faces: {len(used_indices)}")
    print(f"Vértices não utilizados: {len(unused_indices)}\n")

    if not unused_indices:
        print("✅ Todos os vértices estão sendo usados nas faces.")
        return

    print("⚠️ Vértices não utilizados:")
    for idx in unused_indices:
        print(f"  {idx}: {vertices[idx - 1]}")


# ===== EXECUÇÃO =====
def main():
    parser = argparse.ArgumentParser(description="Analisa um arquivo .obj e identifica vértices não utilizados.")
    parser.add_argument('filepath', type=str, help="Caminho para o arquivo .obj")

    args = parser.parse_args()
    input_obj = args.filepath

    print(f"Lendo arquivo: {input_obj}")
    vertices, faces = parse_obj_file(input_obj)
    used_indices = get_used_vertex_indices(faces)
    print_unused_vertices(vertices, used_indices)


if __name__ == '__main__':
    main()
