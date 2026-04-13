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
        print("Usage: python extract_docx.py <docx_file>")
        sys.exit(1)

    docx_path = sys.argv[1]
    try:
        text = extract_text_from_docx(docx_path)
        print(text[:5000])  # Print first 5000 chars to avoid huge output
    except Exception as e:
        print(f"Error extracting text: {e}")
        sys.exit(1)