// jest.config.js
export const roots = ['<rootDir>/src', '<rootDir>/Tests'];
export const testMatch = [
    '**/?(*.)+(spec|test).[tj]s?(x)'
];
export const transform = {
    '^.+\\.(js|jsx)$': 'babel-jest'
};
export const setupFilesAfterEnv = ['<rootDir>/setupTests.js'];