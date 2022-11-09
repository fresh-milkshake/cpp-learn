from collections import defaultdict
from typing import Dict, List, Tuple
import os
import string

import rich
from rich import table
from tqdm import tqdm
from fuzzywuzzy import process, fuzz
import logging

logging.basicConfig(level=logging.CRITICAL)

FILE_DIR = os.path.dirname(os.path.abspath(__file__))
MARKDOWN_PATH = os.path.join(FILE_DIR, "markdown")


def search(context: str, query: str) -> Tuple[int,  Dict[str, Tuple[int, str, int]]] | None:
    ''' 
    Поиск определенной фразы или подстроки в данном контексте.

    :context: список названий файлов для поиска
    :query: фраза или подстрока для поиска

    :return: название файла и строка
    '''
    results = {}
    lines_count = 0
    for file in tqdm(os.listdir(context), desc='Обработка файлов',
                     unit='file'):
        with open(os.path.join(context, file), 'r', encoding='utf-8') as f:
            text = f.read()
            lines = text.splitlines()
            lines_count += len(lines)
            file_results = []
            for num, line in tqdm(enumerate(lines),
                                  desc='Поиск в файле',
                                  unit='line'):
                found = fuzz.partial_ratio(line, [query])
                if found > 50:
                    file_results.append([found, line, num])
            if file_results:
                results[file] = sorted(file_results,
                                       key=lambda x: x[0],
                                       reverse=True)
    return lines_count, results


def count_chars(dir: str) -> int:
    '''
    Подсчет количества символов в файлах в директории.

    :files: список файлов       

    :return: количество строк
    '''
    count = 0
    for file in os.listdir(dir):
        with open(os.path.join(dir, file), 'r', encoding='utf-8') as f:
            for line in f:
                for i in line:
                    if i in string.ascii_letters:
                        count += 1
    return count


def main():
    while 1:
        query = input('Введите фразу или подстроку для поиска: ')
        if not query:
            rich.print(
                '[bold red][:error:] Введите фразу или подстроку для поиска[/]'
            )
            continue
        break

    count, results = search(MARKDOWN_PATH, query)  # type: ignore

    if not results:
        rich.print('[bold yellow]:warning:  Ничего не найдено[/]')

    os.system('cls' if os.name == 'nt' else 'clear')
    rich.print(f'Всего строк в файлах: {count}')
    for matched in results:
        file_matches = results[matched]  # type: ignore
        matches = table.Table(
            title=
            f'В файле [bold blue]{matched}[/] найдено [bold blue]{len(file_matches)}[/] совпадение(-ий)'
        )
        matches.add_column('Номер строки', justify='center')
        matches.add_column('Совпадение (%)', justify='center')
        matches.add_column('Текст', justify='left')
        matches.add_column('"Ссылка"', justify='center', style='dim')
        for match in file_matches:
            matches.add_row(str(match[2]), str(match[0]), match[1].strip(),
                            f'[italic white]{matched}#{match[2]}[/]')
        rich.print(matches)


if __name__ == '__main__':
    main()