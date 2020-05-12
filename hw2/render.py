import os

custom_tpl = os.path.join('prebuilt', 'print.md')
default_tpl = os.path.join('prebuilt', 'template.md')
template = custom_tpl if os.path.isfile(custom_tpl) else default_tpl

template = open(template).read()

args = { f'tab{n}' : open(os.path.join('mkd', f'{n}.md')).read() for n in [3, 5, 7] }
output = template.format(**args)
print(output)
