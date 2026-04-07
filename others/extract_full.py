#!/usr/bin/env python3
import zipfile
import xml.etree.ElementTree as ET
import sys

def extract_text_from_docx(docx_path):
    # Open the docx file (which is a zip archive)
    with zipfile.ZipFile(docx_path, 'r') as docx:
        # Read the main document XML
        xml_content = docx.read('word/document.xml')

    # Parse the XML
    # WordprocessingML namespace
    ns = {'w': 'http://schemas.openxmlformats.org/wordprocessingml/2006/main'}

    root = ET.fromstring(xml_content)

    # Find all text elements
    text_elements = root.findall('.//w:t', ns)

    # Extract text and join with spaces
    texts = [elem.text for elem in text_elements if elem.text]

    # Return as a single string
    return ' '.join(texts)

if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python extract_full.py <docx_file> [output_file]")
        sys.exit(1)

    docx_path = sys.argv[1]
    output_file = sys.argv[2] if len(sys.argv) > 2 else None

    try:
        text = extract_text_from_docx(docx_path)
        if output_file:
            with open(output_file, 'w', encoding='utf-8') as f:
                f.write(text)
            print(f"Text extracted to {output_file}")
        else:
            print(text)
    except Exception as e:
        print(f"Error extracting text: {e}")
        sys.exit(1)